#pragma once

class NpcHandler
{
public:
	static SendBufferRef MakeSendBuffer(Npc::GameData pkt, Npc::INGAME type);
	static SendBufferRef MakeSendBuffer(Npc::LoginData pkt, Npc::INGAME type);
	static SendBufferRef MakeSendBuffer(Npc::StartData pkt, Npc::INGAME type);

	static void HandlerPacket(PacketSessionRef& ref, BYTE* buffer, int32 len);

private:
	static void HandlerLogin(PacketSessionRef& ref, Npc::LoginData&& pkt);
	static void HandlerGame(PacketSessionRef& ref, Npc::GameData&& pkt);

public:
	
};

struct NpcHeader {
	google::protobuf::uint32 size;
	Npc::INGAME type;
};