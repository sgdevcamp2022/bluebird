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

SendBufferRef NpcHandler::MakeSendBuffer(Npc::StartData pkt, Npc::INGAME type)
{
	return _MakeSendBuffer<Npc::StartData, NpcHeader, Npc::INGAME>(pkt, type);
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
		break;
	default:
		break;
	}
}

void NpcHandler::HandlerLogin(PacketSessionRef& ref, Npc::LoginData&& pkt)
{
	//TODO 게임 실행 확인
	cout << "새로 생성 확인" << endl;

	map<int64, ObtacleRef> datas;
	
	if (pkt.obstacle_size() != 0) {
		for (int i = 0; i < pkt.obstacle_size(); i++) {
			auto data = pkt.obstacle(i);
			if (data.has_position() && data.has_rotation()) {
				datas[data.id()] = make_shared<Obtacle>(data.id(), data.shape(), pkt.matchroom(), Vector3(data.position()), Vector3(data.rotation()), data.speed(), data.direction());
			}
		}
		Ggames->GetRoomRef(pkt.matchroom())->DoAsync(&Room::ObstacleEnter, &datas);
	}
}

void NpcHandler::HandlerGame(PacketSessionRef& ref, Npc::GameData&& pkt)
{
	Protocol::Move data;
	data.set_id(pkt.id());
	data.set_time(GetTickCount64());

	//복사 비용 줄이기
	cout << pkt.rotation().x() << pkt.rotation().y() << pkt.rotation().z() << endl;
	Ggames->GetRoomRef(pkt.matchroom())->DoAsync(&Room::ObstacleMove, pkt.id(), pkt.position(), pkt.rotation(), std::move(data));
}
