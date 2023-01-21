#pragma once

class PacketHandler
{
public:
	static SendBufferRef MakeSendBuffer(Protocol::Data pkt, Protocol::INGAME type);

	static void HandlerPacket(PacketSessionRef& ref, BYTE* buffer, int32 len);
private:
	static void HandlerMatch(PacketSessionRef& ref, Match::Users&& pkt);

private:
	static void HandlerConnect(PacketSessionRef& ref, Protocol::Data&& pkt);
	static void HandlerMove(PacketSessionRef& ref, Protocol::Data&& pkt);
	//static void HandlerConnect(PacketSessionRef& ref, )
};

//struct PacketHeader {
//	google::protobuf::uint32 size;
//	Match::STATE type;
//};

struct PacketHeader {
	google::protobuf::uint32 size;
	Protocol::INGAME type;
};

template<typename T>
inline SendBufferRef _MakeSendBuffer(T& pkt, Protocol::INGAME type)
{
	const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
	const uint16 packetSize = dataSize + sizeof(PacketHeader);

	SendBufferRef sendBuffer = GSendBufferManager->Open(packetSize);
	PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
	header->size = dataSize;
	header->type = type;
	ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
	sendBuffer->Close(packetSize);

	return sendBuffer;
}

template<typename Packet_Type>
inline Packet_Type ParsingPacket(BYTE* buffer, int32 len)
{
	Packet_Type pkt;
	pkt.ParseFromArray(buffer + sizeof(PacketHeader), len);

	return pkt;
}