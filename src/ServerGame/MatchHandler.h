#pragma once

class MatchHandler
{
public:
	static SendBufferRef MakeSendBuffer(Match::S_Match pkt, Match::STATE type);

	static void HandlerPacket(PacketSessionRef& ref, BYTE* buffer, int32 len);
private:
	static void HandlerMatch(PacketSessionRef& ref, Match::S_Match&& pkt);
};

struct MatchHeader
{
	google::protobuf::uint32 size;
	Match::STATE type;
};