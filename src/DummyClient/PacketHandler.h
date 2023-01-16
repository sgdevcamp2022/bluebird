#pragma once

class PacketHandler
{
public:
	static void HandlerPacket(PacketSessionRef& ref, BYTE* buffer, int32 len);

	static SendBufferRef MakeSendBuffer(Protocol::S_DATA pkt, Protocol::STATE type);

private:
	static void HandlerLogin(PacketSessionRef& ref, Protocol::S_DATA&& pkt);
	static void HandlerMatch(PacketSessionRef& ref, Protocol::S_DATA&& pkt);
};

struct PacketHeader {
	google::protobuf::uint32 size;
	Protocol::STATE type;
};

template<typename T>
inline SendBufferRef _MakeSendBuffer(T& pkt, Protocol::STATE type)
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