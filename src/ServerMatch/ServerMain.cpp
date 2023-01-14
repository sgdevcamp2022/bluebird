#include "pch.h"
#include "MatchSession.h"

int main()
{
	ServerServiceRef service = make_shared<ServerService>();
	service->SetFactory(make_shared<MatchSession>);
	service->SetIocpCore(make_shared<IocpCore>());
	service->SetNetAddress(NetAddress(L"127.0.0.1", 8000));

	if (!service->Start())
		HandleError("Start Error");

	for (int i = 0; i < THREAD_SIZE; i++) {
		GThreadPool->enqueue([=]()
			{
				while (true) {
					service->GetIocpCore()->Dispatch();
				}
			});
	}
	GThreadPool->Join();
}