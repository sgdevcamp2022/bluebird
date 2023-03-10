#include "pch.h"
#include "GameSession.h"
#include "NpcSession.h"
#include "MatchSession.h"
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

		ThreadManager::DistributeReservedJobs();

		ThreadManager::DoGlobalQueueWork();
	}
}

int main() {

	ServerServiceRef matchService = MakeShared<ServerService>(
		NetAddress(L"127.0.0.1", 7000),
		MakeShared<IocpCore>(),
		MakeShared<MatchSession>, 1);
	ServerServiceRef gameService = MakeShared<ServerService>(
		NetAddress(L"192.168.0.224", 5000),
		MakeShared<IocpCore>(),
		MakeShared<GameSession>, 10);
	ServerServiceRef npcService = MakeShared<ServerService>(
		NetAddress(L"192.168.0.224", 4000),
		MakeShared<IocpCore>(),
		MakeShared<NpcSession>, 5);
	
	ASSERT_CRASH(matchService->Start());
	ASSERT_CRASH(gameService->Start());	
	ASSERT_CRASH(npcService->Start());

	for (int i = 0; i < THREAD_SIZE + THREAD_SIZE; i++) {
		GThreadManager->Launch([&gameService]()
			{
				while (true)
				{
					DoWorkerJob(gameService);
				}
			});
	}
	if (!NPC_TEST) {
		for (int i = 0; i < THREAD_SIZE; i++) {
			GThreadManager->Launch([&npcService]()
				{
					while (true)
					{
						DoWorkerJob(npcService);
					}
				});
		}
	}

	DoWorkerJob(matchService);

	GThreadManager->Join();
}