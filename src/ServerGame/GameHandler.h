#pragma once

class GameHandler
{
public:
	static SendBufferRef MakeSendBuffer(Protocol::Data pkt, Protocol::INGAME type);

	static void HandlerPacket(PacketSessionRef& ref, BYTE* buffer, int32 len);

private:
	static void HandlerConnect(PacketSessionRef& ref, Protocol::Data&& pkt);
	static void HandlerMove(PacketSessionRef& ref, Protocol::Data&& pkt);
};

struct GameHeader {
	google::protobuf::uint32 size;
	Protocol::INGAME type;
};