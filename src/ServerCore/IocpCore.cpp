#include "pch.h"
#include "IocpCore.h"
#include "IocpEvent.h"

IocpCore::IocpCore()
{
	_iocpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	if (_iocpHandle == INVALID_HANDLE_VALUE)
		HandleError("CreateIoCOmpletionPort");
}

IocpCore::~IocpCore()
{
	::CloseHandle(_iocpHandle);
}

bool IocpCore::Register(IocpObjectRef iocpobject)
{
	return CreateIoCompletionPort(iocpobject->GetHandle(), _iocpHandle, 0, 0);
}

bool IocpCore::Dispatch(uint32 timeoutMS)
{
	DWORD numOfBytes = 0 ;
	ULONG_PTR key = 0;
	IocpEvent* iocpEvent = nullptr;

	if (GetQueuedCompletionStatus(_iocpHandle, &numOfBytes, &key, reinterpret_cast<LPOVERLAPPED*>(&iocpEvent), timeoutMS)) {
		IocpObjectRef iocpObject = iocpEvent->owner;
		iocpObject->Dispatch(iocpEvent, numOfBytes);
	}else
	{
		int32 errCode = ::WSAGetLastError();
		switch (errCode)
		{
		case WAIT_TIMEOUT:
			return false;
		default:
			// TODO : ·Î±× Âï±â
			IocpObjectRef iocpObject = iocpEvent->owner;
			iocpObject->Dispatch(iocpEvent, numOfBytes);
			break;
		}
	}

	return true;
}
