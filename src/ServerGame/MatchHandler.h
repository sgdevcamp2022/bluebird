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