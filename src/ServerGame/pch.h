#pragma once

#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#ifdef _DEBUG
#pragma comment(lib, "ServerCore\\Debug\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Debug\\libprotobufd.lib")
#else
#pragma comment(lib, "ServerCore\\Release\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Release\\libprotobufd.lib")
#endif

#include <CorePch.h>
#include <Service.h>

using PacketSessionRef	= shared_ptr<class PacketSession>;
using GameSessionRef	= shared_ptr<class GameSession>;
using MatchSessionRef	= shared_ptr<class MatchSession>;
using NpcSessionRef		= shared_ptr<class NpcSession>;
using PlayerRef			= shared_ptr<class Player>;
using ObtacleRef		= shared_ptr<class Obtacle>;
using RoomRef			= shared_ptr<class Room>;

#include "ProtocolMatch.pb.h"
#include "ProtocolServer.pb.h"
#include "ProtocolConnect.pb.h"
#include "ProtocolNpc.pb.h"

#include "PacketSession.h"
#include "GameSession.h"
#include "MatchSession.h"
#include "NpcSession.h"
#include "Constant.h"

#include "GameHandler.h"
#include "MatchHandler.h"
#include "NpcHandler.h"
#include "GameObject.h"
#include "Room.h"
#include "Games.h"

#include "GameUtils.h"

