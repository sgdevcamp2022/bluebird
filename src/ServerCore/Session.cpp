#include "pch.h"
#include "Session.h"
#include "SocketUtils.h"

Session::Session() : _recv_buffer(BUFFER_SIZE)
{
	_sock = SocketUtils::CreateSocket();
}

Session::~Session()
{
	SocketUtils::Close(_sock);
}

void Session::Send(SendBufferRef buffer)
{
	if (IsConnected() == false)
		return;

	bool registerSend = false;

	{
		lock_guard<SpinLock> guard(_lock);

		_send_queue.push(buffer);

		if (_send_registered.exchange(true) == false)
			registerSend = true;
	}

	if (registerSend)
		RegisterSend();
}

bool Session::Connect()
{
	return RegisterConnect();
}

void Session::DisConnect(const WCHAR* cause)
{
	if (_connected.exchange(false) == false)
		return;

	// TEMP
	wcout << "Disconnect : " << cause << endl;

	RegisterDisconnect();
}

HANDLE Session::GetHandle()
{
	return reinterpret_cast<HANDLE>(_sock);
}

void Session::Dispatch(IocpEvent* iocpEvent, int32 numOfBytes)
{
	switch (iocpEvent->GetType()) {
	case EventType::Connect:
		ProcessConnect();
		break;
	case EventType::Recv:
		ProcessRecv(numOfBytes);
		break;
	case EventType::Disconnect:
		ProcessDisconnect();
		break;
	case EventType::Send:
		ProcessSend(numOfBytes);
		break;
	default:
		break;
	}
}

void Session::ProcessSend(int32 numOfBytes)
{
	_send_event.owner = nullptr;
	_send_event.send_buffers.clear();

	if (numOfBytes == 0) {
		DisConnect(L"Send 0");
		return;
	}

	OnSend(numOfBytes);

	{
		lock_guard<SpinLock> guard(_lock);
		if (_send_queue.empty())
			_send_registered.store(false);
		else
			RegisterSend();
	}
}

void Session::ProcessRecv(int32 numOfBytes)
{
	_recvEvent.owner = nullptr;

	if (numOfBytes == 0) {
		DisConnect(L"Recv 0");
		return;
	}
	// 제대로 정보가 다 들어왔는지 체크 필요
	if (_recv_buffer.OnWrite(numOfBytes) == false) {
		DisConnect(L"OnWrite Overflow 0");
		return;
	}

	int32 data_size = _recv_buffer.Data_size();
	int32 process_len = OnRecv(_recv_buffer.Read_pos(), data_size);
	if (process_len < 0 || data_size < process_len || _recv_buffer.OnRead(process_len) == false) {
		DisConnect(L"OnRead Overflow 0");
		return;
	}

	_recv_buffer.Clean();

	RegisterRecv();
}

void Session::ProcessDisconnect()
{
	_disconnectEvent.owner = nullptr;

	OnDisconnected(); // 컨텐츠 코드에서 재정의
	GetService()->ReleaseSession(GetSessionRef());
}

void Session::ProcessConnect()
{
	_connectEvent.owner = nullptr;

	_connected.store(true);

	// 세션 등록
	GetService()->AddSession(GetSessionRef());

	// 컨텐츠 코드에서 재정의
	OnConnected();

	// 수신 등록
	RegisterRecv();
}

void Session::RegisterSend()
{
	if (IsConnected() == false)
		return;

	_send_event.Init();
	_send_event.owner = shared_from_this();

	{
		lock_guard<SpinLock> guard(_lock);
		
		int32 write_size = 0;
		while (_send_queue.empty() == false) {
			SendBufferRef send_buffer = _send_queue.front();

			write_size += send_buffer->WriteSize();
			//TODO

			_send_queue.pop();
			_send_event.send_buffers.push_back(send_buffer);
		}
	}

	//Scatter-Gatter (흩어져 있는 데이터들을 모아서 한 방에 보낸다)
	vector<WSABUF> wsa_bufs;
	wsa_bufs.reserve(_send_event.send_buffers.size());

	for (SendBufferRef send_buffer : _send_event.send_buffers)
	{
		WSABUF wsa_buf;
		wsa_buf.buf = reinterpret_cast<char*>(send_buffer->Buffer());
		wsa_buf.len = static_cast<LONG>(send_buffer->WriteSize());
		wsa_bufs.push_back(wsa_buf);
	}

	DWORD num_of_bytes = 0;
	if (SOCKET_ERROR == WSASend(_sock, wsa_bufs.data(), static_cast<DWORD>(wsa_bufs.size()), &num_of_bytes, 0, &_send_event, nullptr)) {
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING){
			HandleError("WSASend");
			_send_event.owner = nullptr; // RELEASE_REF
			_send_event.send_buffers.clear();
			_send_registered.store(false);
		}
	}
}

void Session::RegisterRecv()
{
	if (IsConnected() == false)
		return;
	_recvEvent.Init();
	_recvEvent.owner = shared_from_this();

	WSABUF wsaBuf;
	wsaBuf.buf = reinterpret_cast<char*>(_recv_buffer.Write_pos());
	wsaBuf.len = _recv_buffer.Free_size();

	DWORD numOfBytes = 0;
	DWORD flag = 0;

	if (SOCKET_ERROR == WSARecv(_sock, &wsaBuf, 1, &numOfBytes, &flag, &_recvEvent, nullptr))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			HandleError("WSARecv");
			_recvEvent.owner = nullptr; // RELEASE_REF
		}
	}
}

bool Session::RegisterDisconnect()
{
	_disconnectEvent.Init();
	_disconnectEvent.owner = shared_from_this();

	if (false == SocketUtils::DisconnectEx(_sock, &_disconnectEvent, TF_REUSE_SOCKET, 0)) {
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING) {
			_disconnectEvent.owner = nullptr;
			return false;
		}
	}
	return true;
}

bool Session::RegisterConnect()
{
	if (IsConnected())
		return false;

	if (GetService()->GetServiceType() != ServiceType::Client)
		return false;

	if (SocketUtils::SetReuseAddress(_sock, true) == false)
		return false;

	if (SocketUtils::BindAnyAddress(_sock, 0) == false)
		return false;

	_connectEvent.Init();
	_connectEvent.owner = shared_from_this();

	DWORD num_of_bytes = 0;
	SOCKADDR_IN sock_addr = GetService()->GetNetAddress().GetSockAddr();
	if (SocketUtils::ConnectEx(_sock, reinterpret_cast<SOCKADDR*>(&sock_addr), sizeof(sock_addr), nullptr, 0, &num_of_bytes, &_connectEvent) == false)
	{
		int32 error_code = ::WSAGetLastError();
		if (error_code != WSA_IO_PENDING) 
		{
			_connectEvent.owner = nullptr;
			return false;
		}
	}

	return true;
}
