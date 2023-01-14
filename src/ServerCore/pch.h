#pragma once

#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#include "Types.h"
#include "CoreTLS.h"
#include "CoreGlobal.h"

#include <windows.h>
#include <iostream>
using namespace std;

#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include<vector>
#include<queue>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<future>
#include<functional>
#include<chrono>
#include<set>
#include<memory>

#include "SpinLock.h"
#include "ThreadPool.h"
#include "Service.h"
#include "Session.h"
#include "Listener.h"
#include "SendBuffer.h"

inline void HandleError(string error) { cout << error << endl; }