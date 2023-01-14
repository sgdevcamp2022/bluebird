#include "pch.h"
#include "Service.h"
#include "Session.h"

Service::Service(ServiceType type, int maxSessionCount)
	: _type(type), _maxSessionCount(maxSessionCount)
{

}

Service::~Service()
{
}

void Service::CloseService()
{
	// TODO
}

SessionRef Service::CreateSession()
{
	SessionRef session = _sessionFactory();
	session->SetService(shared_from_this());

	if (_iocpCore->Register(session) == false)
		return nullptr;

	return session;
}

void Service::AddSession(SessionRef session)
{
	lock_guard<SpinLock> guard(_lock);
	_sessionCount++;
	_sessions.insert(session);
}

void Service::ReleaseSession(SessionRef session)
{
	lock_guard<SpinLock> guard(_lock);
	_sessions.erase(session);
	_sessionCount--;

}

ServerService::ServerService(int maxSessionCount)
	:Service(ServiceType::Server, maxSessionCount) {}

bool ServerService::Start()
{
	if (CanStart() == false) {
		return false;
	}
	
	_listener = make_shared<Listener>();
	if (_listener == nullptr) {
		return false;
	}

	if (_listener->StartAccept(static_pointer_cast<ServerService>(shared_from_this())) == false) {
		return false;
	}
	return true;
}

void ServerService::SetFactory(SessionFactory factory)
{
	_sessionFactory = factory;
}

void ServerService::SetNetAddress(NetAddress address)
{
	_netAddress = address;
}

void ServerService::SetIocpCore(IocpCoreRef core)
{
	_iocpCore = core;
}

void ServerService::CloseService()
{
	Service::CloseService();
}

ClientService::ClientService(int maxSessionCount)
	: Service(ServiceType::Client, maxSessionCount) {}

bool ClientService::Start()
{
	if (CanStart() == false)
		return false;
	const int32 sessionCount = GetMaxSessionCount();
	for (int32 i = 0; i < sessionCount; i++)
	{
		SessionRef session = CreateSession();
		if (session->Connect() == false)
			return false;
	}

	return true;
}

void ClientService::CloseService()
{
	Service::CloseService();
}

void ClientService::SetFactory(SessionFactory factory)
{
	_sessionFactory = factory;
}

void ClientService::SetNetAddress(NetAddress address)
{
	_netAddress = address;
}

void ClientService::SetIocpCore(IocpCoreRef core)
{
	_iocpCore = core;
}
