#pragma once

class GameHandler
{
public:
	static SendBufferRef MakeSendBuffer(Protocol::Data pkt, Protocol::INGAME type);
	static SendBufferRef MakeSendBuffer(Protocol::Move pkt, Protocol::INGAME type);
	static void HandlerPacket(PacketSessionRef& ref, BYTE* buffer, int32 len);

private:
	static void HandlerConnect(PacketSessionRef& ref, Protocol::Player&& pkt);
	static void HandlerMove(PacketSessionRef& ref, Protocol::Move&& pkt);
	static void HandlerOBMove(PacketSessionRef& ref, Protocol::Data&& pkt);
	static void HandlerStart(PacketSessionRef& ref, Protocol::Data&& pkt);
};

struct GameHeader {
	google::protobuf::uint32 size;
	Protocol::INGAME type;
};

template<typename Packet_Type, typename Header_Type>
inline Packet_Type ParsingPacket(BYTE* buffer, int32 len)
{
	Packet_Type pkt;
	pkt.ParseFromArray(buffer + sizeof(Header_Type), len);

	return pkt;
}

template<typename T, typename Header, typename S>
inline SendBufferRef _MakeSendBuffer(T& pkt, S type)
{
	const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
	const uint16 packetSize = dataSize + sizeof(Header);

	SendBufferRef sendBuffer = GSendBufferManager->Open(packetSize);
	Header* header = reinterpret_cast<Header*>(sendBuffer->Buffer());
	header->size = dataSize;
	header->type = type;
	ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
	sendBuffer->Close(packetSize);

	return sendBuffer;
}