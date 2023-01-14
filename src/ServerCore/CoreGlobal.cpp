#include "pch.h"
#include "CoreGlobal.h"
#include "SocketUtils.h"

ThreadPool* GThreadPool = nullptr;
class CoreGlobal {
public:
	CoreGlobal() {
		GThreadPool = new ThreadPool(10);
		SocketUtils::Init();
	}

	~CoreGlobal() {
		delete GThreadPool;
		SocketUtils::Clear();
	}
}GCoreGlobal;