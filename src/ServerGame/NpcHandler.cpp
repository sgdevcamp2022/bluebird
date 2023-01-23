#include "pch.h"
#include "NpcHandler.h"

SendBufferRef NpcHandler::MakeSendBuffer(Npc::GameData pkt, Npc::INGAME type)
{
	return _MakeSendBuffer<Npc::GameData, NpcHeader, Npc::INGAME>(pkt, type);
}

SendBufferRef NpcHandler::MakeSendBuffer(Npc::LoginData pkt, Npc::INGAME type)
{
	return _MakeSendBuffer<Npc::LoginData, NpcHeader, Npc::INGAME>(pkt, type);
}

void NpcHandler::HandlerPacket(PacketSessionRef& ref, BYTE* buffer, int32 len)
{
	NpcHeader* head = reinterpret_cast<NpcHeader*>(buffer);
	switch (head->type) {
	case Npc::LOGIN:
		HandlerLogin(ref, ParsingPacket<Npc::LoginData, NpcHeader>(buffer, len));
		break;
	case Npc::GAME:
		HandlerGame(ref, ParsingPacket<Npc::GameData, NpcHeader>(buffer, len));
	}
}

void NpcHandler::HandlerLogin(PacketSessionRef& ref, Npc::LoginData&& pkt)
{
	cout << "새로 생성 확인" << endl;
}

void NpcHandler::HandlerGame(PacketSessionRef& ref, Npc::GameData&& pkt)
{
	for (int i = 0; i < pkt.obstaclesize(); i++) {
		Npc::Obstacle obstacle = pkt.obstacle(i);
		cout << obstacle.id() << " " << obstacle.x() << " " << obstacle.y() << " " << obstacle.z() << " "<<endl;
	}

	ref->Send(MakeSendBuffer(pkt, Npc::GAME));
}
