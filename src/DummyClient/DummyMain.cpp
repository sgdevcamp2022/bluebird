#include "pch.h"
#include <pch.h>
#include "MatchSession.h"
#include "PacketSession.h"

int main() {
	ClientServiceRef service = make_shared<ClientService>(10);
	service->SetFactory(make_shared<MatchSession>);
	service->SetIocpCore(make_shared<IocpCore>());
	service->SetNetAddress(NetAddress(L"127.0.0.1", 8000));

	if (!service->Start())
		HandleError("Start Error");

	for (int i = 0; i < 10; i++) {
		GThreadPool->enqueue([=]()
			{
				while (true) {
					service->GetIocpCore()->Dispatch();
				}
			});
	}
	GThreadPool->Join();
}