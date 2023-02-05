#pragma once

class MatchHandler
{
public:
	static SendBufferRef MakeSendBuffer(Match::Data pkt, Match::STATE type);

	static void HandlerPacket(PacketSessionRef& ref, BYTE* buffer, int32 len);
private:
	static void HandlerMatch(PacketSessionRef& ref, Match::Users&& pkt);
};

template<typename T>
inline SendBufferRef _MatchMaker(T& pkt, Match::STATE type)
{
	const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
	const uint16 packetSize = dataSize + sizeof(Match::Header);

	SendBufferRef sendBuffer = GSendBufferManager->Open(packetSize);
	Match::Header* header = reinterpret_cast<Match::Header*>(sendBuffer->Buffer());
	header->set_size(dataSize);
	header->set_state(type);

	cout << header->size() << endl;
	ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
	sendBuffer->Close(packetSize);

	return sendBuffer;
}

template<typename Packet_Type>
inline Packet_Type _MatchParsing(BYTE* buffer, int32 len)
{
	Packet_Type pkt;
	pkt.ParseFromArray(buffer + sizeof(Match::Header), len);

	return pkt;
}