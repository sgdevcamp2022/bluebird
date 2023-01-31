#include "pch.h"
#include "Gamehandler.h"
#include "GameSession.h"
#include "MatchSession.h"

void GameHandler::HandlerPacket(PacketSessionRef& ref, BYTE* buffer, int32 len)
{
    GameHeader* head = reinterpret_cast<GameHeader*>(buffer);
    switch (head->type)
    {
    case Protocol::CONNECT:
        HandlerConnect(ref, ParsingPacket<Protocol::Player, GameHeader>(buffer, (int32)head->size));
        break;
    case Protocol::PLAYER_MOVE:
        HandlerMove(ref, ParsingPacket<Protocol::Move, GameHeader>(buffer, (int32)head->size));
        break;
    case Protocol::OBSTACLE_MOVE:
        HandlerOBMove(ref, ParsingPacket<Protocol::Data, GameHeader>(buffer, (int32)head->size));
        break;
    case Protocol::START:
        HandlerStart(ref, ParsingPacket<Protocol::Data, GameHeader>(buffer, (int32)head->size));
        break;
    default:
        break;
    }
}

void GameHandler::HandlerConnect(PacketSessionRef& ref, Protocol::Player&& pkt)
{
    auto point = pkt.position();
    cout << "Connect(" << pkt.id() << ") : " << point.x() << " " << point.y() << " " << point.z() << endl;
}

void GameHandler::HandlerMove(PacketSessionRef& ref, Protocol::Move&& pkt)
{
    auto point = pkt.position();
    cout << "whitch(" << pkt.id() << ") : " << point.x() << " " << point.y() << " " << point.z() << endl;
}


void GameHandler::HandlerOBMove(PacketSessionRef& ref, Protocol::Data&& pkt)
{
    cout << "Ob Move" << pkt.obtacle_size() << endl;
}

void GameHandler::HandlerStart(PacketSessionRef& ref, Protocol::Data&& pkt)
{
    cout << "½ÃÀÛÇÔ" << pkt.player_size() << endl;
    GameSessionRef session = static_pointer_cast<GameSession>(ref);
    this_thread::sleep_for(1s);
    {
        Protocol::Move pkt;
        pkt.set_id(session->id);
        auto player = pkt.mutable_position();
        player->set_x(1.0f);
        player->set_y(2.0f);
        player->set_z(3.0f);
        session->Send(GameHandler::MakeSendBuffer(pkt, Protocol::PLAYER_MOVE));
    }
}

SendBufferRef GameHandler::MakeSendBuffer(Protocol::Data pkt, Protocol::INGAME type)
{
    return _MakeSendBuffer<Protocol::Data, GameHeader, Protocol::INGAME>(pkt, type);
}
SendBufferRef GameHandler::MakeSendBuffer(Protocol::Move pkt, Protocol::INGAME type)
{
    return _MakeSendBuffer<Protocol::Move, GameHeader, Protocol::INGAME>(pkt, type);
}