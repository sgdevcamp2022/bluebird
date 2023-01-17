#include "pch.h"
#include "MatchSession.h"
#include "ConnectSession.h"
#include "MatchManager.h"
#include <CoreGlobal.h>
#include <ThreadManager.h>

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
		
		ThreadManager::DoGlobalQueueWork();
	}
}

int main()
{
	ServerServiceRef Sservice = MakeShared<ServerService>(
		NetAddress(L"127.0.0.1", 8000),
		MakeShared<IocpCore>(),
		MakeShared<MatchSession>, 10);

	ClientServiceRef Cservice = MakeShared<ClientService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<ConnectSession>, 1);

	GMatch->SetService(Cservice);

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