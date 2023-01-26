#include "pch.h"
#include "Gamehandler.h"
#include "GameSession.h"
#include "MatchSession.h"
#include "Games.h"
#include "Creature.h"

void GameHandler::HandlerPacket(PacketSessionRef& ref, BYTE* buffer, int32 len)
{
    GameHeader* head = reinterpret_cast<GameHeader*>(buffer);
    switch (head->type)
    {
    case Protocol::CONNECT:
        HandlerConnect(ref, ParsingPacket<Protocol::Data, GameHeader>(buffer, (int32)head->size));
        break;
    case Protocol::MOVE:
        HandlerMove( ref, ParsingPacket<Protocol::Data, GameHeader>(buffer, (int32)head->size));
        break;
    default:
        break;
    }
}

void GameHandler::HandlerConnect(PacketSessionRef& ref, Protocol::Data&& pkt)
{
    GameSessionRef gameSession = static_pointer_cast<GameSession>(ref);

    cout << "Player Inside = " << pkt.id() << " " << pkt.maplevel() << " " << pkt.matchroom() << endl;
    if(gameSession->_mySelf == nullptr)
        Ggames->DoAsync(&Games::EnterGame, gameSession, pkt.id(), pkt.matchroom());

    //접속 시 전체 유저 정보 전달 -> 고민 이슈
}

void GameHandler::HandlerMove(PacketSessionRef& ref, Protocol::Data&& pkt)
{
    GameSessionRef gameSession = static_pointer_cast<GameSession>(ref);
    if (gameSession->_mySelf != nullptr) {
        Protocol::Player point = pkt.player(0);

        if (auto room = gameSession->_room.lock()) {
            if (room->_start)
                room->DoAsync(&Room::PlayerMove, pkt);
        }
    }
}

SendBufferRef GameHandler::MakeSendBuffer(Protocol::Data pkt, Protocol::INGAME type)
{
    return _MakeSendBuffer<Protocol::Data, GameHeader, Protocol::INGAME>(pkt, type);
}
