#pragma once
#include "MatchSession.h"
#include "GameSession.h"
#include "NpcSession.h"
#include <ThreadManager.h>

class MainService
{
public:
	MainService() {
		matchService = MakeShared<ServerService>(
			NetAddress(L"127.0.0.1", 7000),
			MakeShared<IocpCore>(),
			MakeShared<MatchSession>, 1);
		gameService = MakeShared<ServerService>(
			NetAddress(L"127.0.0.1", 5000),
			MakeShared<IocpCore>(),
			MakeShared<GameSession>, 10);
		npcService = MakeShared<ServerService>(
			NetAddress(L"127.0.0.1", 8000),
			MakeShared<IocpCore>(),
			MakeShared<NpcSession>, 10);
		npcMainService = MakeShared<ServerService>(
			NetAddress(L"127.0.0.1", 8001),
			MakeShared<IocpCore>(),
			MakeShared<NpcSession>, 1);
	}

	void Start() {
		ASSERT_CRASH(matchService->Start());
		ASSERT_CRASH(gameService->Start());
		ASSERT_CRASH(npcService->Start());
		ASSERT_CRASH(npcMainService->Start());
	}

	void Join() {
		for (int i = 0; i < THREAD_SIZE; i++) {
			GThreadManager->Launch([=]()
				{
					while (true)
					{
						DoWorkerJob(gameService);
					}
				});
		}
		for (int i = 0; i < THREAD_SIZE; i++) {
			GThreadManager->Launch([=]()
				{
					while (true)
					{
						DoWorkerJob(npcService);
					}
				});
		}

		GThreadManager->Launch([=]()
			{
				while (true)
				{
					DoWorkerJob(npcMainService);
				}
			});

		DoWorkerJob(matchService);

		GThreadManager->Join();
	}

	ServerServiceRef GetMatch() { return gameService; }
	ServerServiceRef GetNpc() { return npcMainService; }
private:
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

private:
	enum
	{
		WORKER_TICK = 64
	};

	ServerServiceRef matchService;
	ServerServiceRef gameService;
	ServerServiceRef npcService;
	ServerServiceRef npcMainService;
};

extern shared_ptr<MainService> service;