#pragma once

class GameHandler
{
public:
	static SendBufferRef MakeSendBuffer(Protocol::Data pkt, Protocol::INGAME type);

	static void HandlerPacket(GameSessionRef ref, BYTE* buffer, int32 len);

private:
	static void HConnect(GameSessionRef& ref, Protocol::Data&& pkt);
	static void HPlayerMove(GameSessionRef& ref, Protocol::Data&& pkt);
	static void HNoMove(GameSessionRef& ref, Protocol::Data&& pkt);
	static void HGameComplete(GameSessionRef& ref, Protocol::Data&& pkt);
	static void HGameFail(GameSessionRef& ref, Protocol::Data&& pkt);
	static void HGameDrop(GameSessionRef& ref, Protocol::Data&& pkt);
	static void HPlayerCrash(GameSessionRef& ref, Protocol::Data&& pkt);
	static void HObstacleCrash(GameSessionRef& ref, Protocol::Data&& pkt);
};

struct GameHeader {
	google::protobuf::uint32 size;
	Protocol::INGAME type;
};