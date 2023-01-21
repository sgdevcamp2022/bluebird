#pragma once

class MatchHandler
{
public:
	static SendBufferRef MakeSendBuffer(Match::Data pkt, Match::STATE type);

	static void HandlerPacket(PacketSessionRef& ref, BYTE* buffer, int32 len);
private:
	static void HandlerMatch(PacketSessionRef& ref, Match::Users&& pkt);
};

struct MatchHeader {
	google::protobuf::uint32 size;
	Match::STATE type;
};

template<typename T, typename S>
inline SendBufferRef _MakeSendBuffer(T& pkt, S type)
{
	const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
	const uint16 packetSize = dataSize + sizeof(MatchHeader);

	SendBufferRef sendBuffer = GSendBufferManager->Open(packetSize);
	MatchHeader* header = reinterpret_cast<MatchHeader*>(sendBuffer->Buffer());
	header->size = dataSize;
	header->type = type;
	ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
	sendBuffer->Close(packetSize);

	return sendBuffer;
}