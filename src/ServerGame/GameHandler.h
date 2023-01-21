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

template<typename T>
inline SendBufferRef _MakeSendBuffer(T& pkt, Protocol::INGAME type)
{
	const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
	const uint16 packetSize = dataSize + sizeof(GameHeader);

	SendBufferRef sendBuffer = GSendBufferManager->Open(packetSize);
	GameHeader* header = reinterpret_cast<GameHeader*>(sendBuffer->Buffer());
	header->size = dataSize;
	header->type = type;
	ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
	sendBuffer->Close(packetSize);

	return sendBuffer;
}