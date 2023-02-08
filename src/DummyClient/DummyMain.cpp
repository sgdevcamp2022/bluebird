#include "pch.h"
#include <CoreGlobal.h>
#include <Service.h>
#include <ThreadManager.h>
#include "MatchSession.h"
#include "PacketSession.h"
#include "GameSession.h"

enum
{
	WORKER_TICK = 64
};

void DoWorkerJob(ClientServiceRef& service)
{
	while (true)
	{
		LEndTickCount = ::GetTickCount64() + WORKER_TICK;

		//네트워크 입출력 처리 -> 인게임 로직까지 (패킷 핸들러에 의해서)
		service->GetIocpCore()->Dispatch(10);

		ThreadManager::DoGlobalQueueWork();
	}
	
}
int main() {
	ClientServiceRef service1 = MakeShared<ClientService>(
		NetAddress(L"127.0.0.1", 6000),
		MakeShared<IocpCore>(),
		MakeShared<MatchSession>, 1);
	ClientServiceRef service2;

	// 테스트 작동 
	// true = NPC
	// false = game client
	bool _test = false;

	if (_test) {
		service2 = MakeShared<ClientService>(
			NetAddress(L"127.0.0.1", 5000),
			MakeShared<IocpCore>(),
			MakeShared<GameSession>, 10);

		ASSERT_CRASH(service1->Start());
		GThreadManager->Launch([&service1]()
			{
				while (true)
				{
					DoWorkerJob(service1);
				}
			});
		this_thread::sleep_for(1s);

		//게임 클라이언트 접속 테스트
		this_thread::sleep_for(5s);
	}
	else {
		service2 = MakeShared<ClientService>(
			NetAddress(L"127.0.0.1", 5000),
			MakeShared<IocpCore>(),
			MakeShared<GameSession>, 1);
	}

	ASSERT_CRASH(service2->Start());
	for (int i = 0; i < THREAD_SIZE; i++) {
		GThreadManager->Launch([&service2]()
			{
				while (true)
				{
					DoWorkerJob(service2);
				}
			});
	}

	GThreadManager->Join();
}