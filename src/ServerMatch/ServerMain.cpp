#include "pch.h"
#include "MatchSession.h"
#include "ConnectSession.h"
#include <CoreGlobal.h>
#include <ThreadManager.h>
#include "RedisManager.h"

enum
{
	WORKER_TICK = 64
};

template<typename T>
void DoWorkerJob(T& service)
{
	while (true)
	{
		LEndTickCount = ::GetTickCount64() + WORKER_TICK;

		//네트워크 입출력 처리 -> 인게임 로직까지 (패킷 핸들러에 의해서)
		service->GetIocpCore()->Dispatch(10);
		
		ThreadManager::DistributeReserveJobs();

		ThreadManager::DoGlobalQueueWork();
	}
}

int main()
{
	ServerServiceRef Sservice = MakeShared<ServerService>(
		NetAddress(L"192.168.0.224", 6000),
		MakeShared<IocpCore>(),
		MakeShared<MatchSession>, 10);

	ClientServiceRef Cservice = MakeShared<ClientService>(
		NetAddress(L"127.0.0.1", 7000),
		MakeShared<IocpCore>(),
		MakeShared<ConnectSession>, 1);

	ASSERT_CRASH(Sservice->Start());
	ASSERT_CRASH(Cservice->Start());

	for (int i = 0; i < THREAD_SIZE; i++) {
		GThreadManager->Launch([&Sservice]()
			{
				while (true)
				{
					DoWorkerJob(Sservice);
				}
			});
	}
	DoWorkerJob(Cservice);

	GThreadManager->Join();
}