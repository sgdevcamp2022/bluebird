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
        HandlerConnect(ref, ParsingPacket<Protocol::Data, GameHeader>(buffer, (int32)head->size));
        break;
    case Protocol::PLAYER_MOVE:
        HandlerMove(ref, ParsingPacket<Protocol::Data, GameHeader>(buffer, (int32)head->size));
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

void GameHandler::HandlerConnect(PacketSessionRef& ref, Protocol::Data&& pkt)
{
    auto point = pkt.player(0);
    cout << "Connect(" << pkt.id() << ") : " << point.x() << " " << point.y() << " " << point.z() << endl;
}

void GameHandler::HandlerMove(PacketSessionRef& ref, Protocol::Data&& pkt)
{
    auto point = pkt.player(0);
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
        Protocol::Data pkt;
        pkt.set_id(session->id);
        pkt.set_maplevel(2);
        pkt.set_matchroom(0);
        auto player = pkt.add_player();
        player->set_x(0.0f);
        player->set_y(0.0f);
        player->set_z(0.0f);
        auto ref = GameHandler::MakeSendBuffer(pkt, Protocol::PLAYER_MOVE);
        session->Send(ref);
    }
}

SendBufferRef GameHandler::MakeSendBuffer(Protocol::Data pkt, Protocol::INGAME type)
{
    return _MakeSendBuffer<Protocol::Data, GameHeader, Protocol::INGAME>(pkt, type);
}
