#pragma once
#include "Constant.h"

class GameHandler
{
private:
	static void HConnect(GameSessionRef& ref, Protocol::ConnectData&& pkt);
	static void HPlayerMove(GameSessionRef& ref, Protocol::Move&& pkt);
	static void HGameComplete(GameSessionRef& ref, Protocol::Player&& pkt);
	static void HGameDrop(GameSessionRef& ref, Protocol::Player&& pkt);
	static void HTime(GameSessionRef& ref, Protocol::Times&& pkt);
	static void HPlayerGoal(GameSessionRef& ref, Protocol::Player&& pkt);

public:
	static void HandlerPacket(GameSessionRef ref, BYTE* buffer, int32 len);

	static SendBufferRef MakeSendBuffer(Protocol::ConnectData pkt, Protocol::INGAME type);
	static SendBufferRef MakeSendBuffer(Protocol::StartData pkt, Protocol::INGAME type);
	static SendBufferRef MakeSendBuffer(Protocol::MoveData pkt, Protocol::INGAME type);
	static SendBufferRef MakeSendBuffer(Protocol::Move pkt, Protocol::INGAME type);
	static SendBufferRef MakeSendBuffer(Protocol::Player pkt, Protocol::INGAME type);
	static SendBufferRef MakeSendBuffer(Protocol::Times pkt, Protocol::INGAME type);
	static SendBufferRef MakeSendBuffer(Protocol::GameCompleteData pkt, Protocol::INGAME type);
	static SendBufferRef MakeSendBuffer(Protocol::PlayerGoalData pkt, Protocol::INGAME type);
	static SendBufferRef MakeSendBuffer(Protocol::SyncPlayer pkt, Protocol::INGAME type);
};

struct GameHeader {
	google::protobuf::uint32 size;
	Protocol::INGAME type;
};