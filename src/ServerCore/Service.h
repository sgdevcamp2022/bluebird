#pragma once

#include "NetAddress.h"
#include "IocpCore.h"
#include "Listener.h"
#include <functional>

enum class ServiceType : uint8
{
	Server,
	Client
};

/*-------------
	Service
--------------*/

using SessionFactory = function<SessionRef(void)>;

class Service : public enable_shared_from_this<Service>
{
public:
	Service(ServiceType type, int maxSessionCount = 1);
	//Service(ServiceType type, NetAddress address,IocpCoreRef core, SessionFactory factory, int32 maxSessionCount = 1);
	virtual ~Service();

	virtual bool		Start() abstract;
	bool				CanStart() { return _sessionFactory != nullptr; }

	virtual void		CloseService();

	SessionRef			CreateSession();
	void				AddSession(SessionRef session);
	void				ReleaseSession(SessionRef session);
	int32				GetCurrentSessionCount() { return _sessionCount; }
	int32				GetMaxSessionCount() { return _maxSessionCount; }

public:
	ServiceType			GetServiceType() { return _type; }
	NetAddress			GetNetAddress() { return _netAddress; }
	IocpCoreRef&		GetIocpCore() { return _iocpCore; }

public:
	virtual void SetFactory(SessionFactory factory) abstract;
	virtual void SetNetAddress(NetAddress address) abstract;
	virtual void SetIocpCore(IocpCoreRef core) abstract;

protected:
	SpinLock			_lock;
	ServiceType			_type;
	NetAddress			_netAddress = {};
	IocpCoreRef			_iocpCore;

	set<SessionRef>		_sessions;
	int32				_sessionCount = 0;
	int32				_maxSessionCount = 0;
	SessionFactory		_sessionFactory;
};

class ServerService : public Service
{
public:
	ServerService(int maxSessionCount = 1);
	//ServerService(NetAddress targetAddress, IocpCoreRef core, SessionFactory factory, int32 maxSessionCount = 1);
	virtual ~ServerService() {}

	virtual bool	Start() override;
	virtual void	CloseService() override;

public:
	virtual void	SetFactory(SessionFactory factory) override;
	virtual void	SetNetAddress(NetAddress address) override;
	virtual void	SetIocpCore(IocpCoreRef core) override;

private:
	ListenerRef		_listener = nullptr;
};

class ClientService : public Service
{
public:
	ClientService(int maxSessionCount = 1);
	//ServerService(NetAddress targetAddress, IocpCoreRef core, SessionFactory factory, int32 maxSessionCount = 1);
	virtual ~ClientService() {}

	virtual bool	Start() override;
	virtual void	CloseService() override;

public:
	virtual void	SetFactory(SessionFactory factory) override;
	virtual void	SetNetAddress(NetAddress address) override;
	virtual void	SetIocpCore(IocpCoreRef core) override;

private:
	ListenerRef		_listener = nullptr;
};