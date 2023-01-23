#include "pch.h"
#include "Gamehandler.h"
#include "GameSession.h"
#include "MatchSession.h"
#include "Room.h"

void GameHandler::HandlerPacket(PacketSessionRef& ref, BYTE* buffer, int32 len)
{
    GameHeader* head = reinterpret_cast<GameHeader*>(buffer);
    switch (head->type)
    {
    case Protocol::CONNECT:
        HandlerConnect(ref, ParsingPacket<Protocol::Data, GameHeader>(buffer, (int32)head->size));
    case Protocol::MOVE:
        HandlerMove(ref, ParsingPacket<Protocol::Data, GameHeader>(buffer, (int32)head->size));
    default:
        break;
    }
}

void GameHandler::HandlerConnect(PacketSessionRef& ref, Protocol::Data&& pkt)
{
    PlayerRef player = make_shared<Player>(pkt.id(), pkt.maplevel());
    player->_ownerSession = static_pointer_cast<GameSession>(ref);
    cout << "Player Inside = " << pkt.id() << " " << pkt.maplevel() << " " << pkt.matchroom();
    GRoom->DoAsync(&Room::GameEnter, static_pointer_cast<GameSession>(ref), player);
}

void GameHandler::HandlerMove(PacketSessionRef& ref, Protocol::Data&& pkt)
{
    Protocol::Player point = pkt.player(0);

    cout << "whitch : " << point.x() << " " << point.y() << " " << point.z();
    ref->Send(MakeSendBuffer(pkt, Protocol::MOVE));
}

SendBufferRef GameHandler::MakeSendBuffer(Protocol::Data pkt, Protocol::INGAME type)
{
    return _MakeSendBuffer<Protocol::Data, GameHeader, Protocol::INGAME>(pkt, type);
}
