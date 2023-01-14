#pragma once
#include "IocpEvent.h"
#include "IocpCore.h"
#include "NetAddress.h"
#include "Service.h"
#include "RecvBuffer.h"

class Session : public IocpObject
{
	friend class Listener;
	friend class IocpCore;
	friend class Service;

	enum {
		BUFFER_SIZE = 0x10000, // 64KB
	};
public:
	Session();
	virtual ~Session();

public:
	void				Send(SendBufferRef buffer);
	bool				Connect();
	void				DisConnect(const WCHAR* cause);

	shared_ptr<Service>	GetService() { return _service.lock(); }
	void				SetService(shared_ptr<Service> service) { _service = service; }

public:
	void				SetNetAddress(NetAddress address) { _addr = address; };
	NetAddress			GetAddress() { return _addr; }
	SOCKET				GetSocket() { return _sock; }
	bool				IsConnected() { return _connected; }
	shared_ptr<Session> GetSessionRef() { return static_pointer_cast<Session>(shared_from_this()); }

private:
	virtual HANDLE		GetHandle() override;
	virtual void		Dispatch(class IocpEvent* iocpEvent, int32 numOfBytes = 0) override;

private:
	void ProcessSend(int32 numOfBytes);
	void ProcessRecv(int32 numOfBytes);
	void ProcessDisconnect();
	void ProcessConnect();

	// 작업 등록
	void RegisterSend();
	void RegisterRecv();
	bool RegisterDisconnect();
	bool RegisterConnect();

protected:
	virtual void OnConnected() { }
	virtual int32 OnRecv(BYTE* buffer, int32 len) { return len; }
	virtual void OnSend(int32 len) { }
	virtual void OnDisconnected() { }

private:
	weak_ptr<Service>		_service;
	NetAddress				_addr = { };
	SOCKET					_sock = INVALID_SOCKET;
	atomic<bool>			_connected = false;

private:
	// 재활용
	DisconnectEvent			_disconnectEvent;
	ConnectEvent			_connectEvent;
	RecvEvent				_recvEvent;
	SendEvent				_send_event;

private:
	RecvBuffer				_recv_buffer;
	SpinLock				_lock;
	queue<SendBufferRef>	_send_queue;
	atomic<bool>			_send_registered = false;

	
};