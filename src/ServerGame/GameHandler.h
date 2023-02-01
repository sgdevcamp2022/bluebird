#pragma once
#include "Constant.h"

class GameHandler
{
private:
	static void HConnect(GameSessionRef& ref, Protocol::Data&& pkt);
	static void HPlayerMove(GameSessionRef& ref, Protocol::Move&& pkt);
	static void HNoMove(GameSessionRef& ref, Protocol::Data&& pkt);
	static void HGameComplete(GameSessionRef& ref, Protocol::Data&& pkt);
	static void HGameFail(GameSessionRef& ref, Protocol::Data&& pkt);
	static void HGameDrop(GameSessionRef& ref, Protocol::Data&& pkt);
	static void HPlayerCrash(GameSessionRef& ref, Protocol::Data&& pkt);
	static void HObstacleCrash(GameSessionRef& ref, Protocol::Data&& pkt);
	static void HTime(GameSessionRef& ref, Protocol::Times&& pkt);

public:
	static void HandlerPacket(GameSessionRef ref, BYTE* buffer, int32 len);

	static SendBufferRef MakeSendBuffer(Protocol::Data pkt, Protocol::INGAME type);
	static SendBufferRef MakeSendBuffer(Protocol::Move pkt, Protocol::INGAME type);
	static SendBufferRef MakeSendBuffer(Protocol::Player pkt, Protocol::INGAME type);
	static SendBufferRef MakeSendBuffer(Protocol::Times pkt, Protocol::INGAME type);
};

struct GameHeader {
	google::protobuf::uint32 size;
	Protocol::INGAME type;
};