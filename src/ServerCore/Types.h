#pragma once
#include <iostream>
#include <memory>

using BYTE = unsigned char;
using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

// shared_ptr
using IocpCoreRef		= std::shared_ptr<class IocpCore>;
using IocpObjectRef		= std::shared_ptr<class IocpObject>;
using SessionRef		= std::shared_ptr<class Session>;
using ListenerRef		= std::shared_ptr<class Listener>;
using ServerServiceRef	= std::shared_ptr<class ServerService>;
using ClientServiceRef	= std::shared_ptr<class ClientService>;
using SendBufferRef		= std::shared_ptr<class SendBuffer>;