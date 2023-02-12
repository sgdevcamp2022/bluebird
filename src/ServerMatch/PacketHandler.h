#pragma once

class PacketHandler
{
public:
	static void HandlerPacket(PacketSessionRef& ref, BYTE* buffer, Match::Header&& head);

	static SendBufferRef MakeSendBuffer(Match::S_Cancle pkt, Match::STATE type);
	static SendBufferRef MakeSendBuffer(Match::S_Login pkt, Match::STATE type);
	static SendBufferRef MakeSendBuffer(Match::S_Match pkt, Match::STATE type);
	static SendBufferRef MakeSuccessBuffer(Match::S_Match pkt, Match::STATE type);

private:
	static void HandlerLogin(PacketSessionRef& ref, Match::C_Login&& pkt);
	static void HandlerCancle(PacketSessionRef& ref, Match::C_Cancle&& pkt);
	static void HandlerCheck(PacketSessionRef& ref, Match::Check&& pkt);
};

template<typename T>
inline SendBufferRef _MakeSendBuffer(T& pkt, Match::STATE type)
{
	const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
	const uint16 packetSize = dataSize + 4;

	SendBufferRef sendBuffer = GSendBufferManager->Open(packetSize);
	char* data = reinterpret_cast<char*>(sendBuffer->Buffer());

	Match::Header header;
	header.set_size(dataSize);
	header.set_state(type);
	string s = header.SerializeAsString();
	s += pkt.SerializeAsString();

	memcpy(data, s.data(), packetSize);
	sendBuffer->Close(packetSize);

	return sendBuffer;
}

template<typename Packet_Type>
inline Packet_Type ParsingPacket(BYTE* buffer, int32 len)
{
	Packet_Type pkt;
	string s;
	s.resize(len);
	memcpy(s.data(), buffer + 4, len);

	pkt.ParseFromString(s);
	return pkt;
}