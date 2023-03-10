#include "pch.h"
#include "Gamehandler.h"
#include "GameSession.h"
#include "MatchSession.h"
#include "Games.h"
#include "GameObject.h"

void GameHandler::HandlerPacket(GameSessionRef ref, BYTE* buffer, int32 len)
{
    GameHeader* head = reinterpret_cast<GameHeader*>(buffer);
    switch (head->type)
    {
    case Protocol::CONNECT:
        HConnect(ref, ParsingPacket<Protocol::ConnectData, GameHeader>(buffer, (int32)head->size));
        break;
    case Protocol::PLAYER_MOVE:
        HPlayerMove(ref, ParsingPacket<Protocol::Move, GameHeader>(buffer, (int32)head->size));
        break;
    case Protocol::PLAYER_DROP:
        HGameDrop(ref, ParsingPacket<Protocol::Move, GameHeader>(buffer, (int32)head->size));
        break;;
    case Protocol::TIME:
        HTime(ref, ParsingPacket<Protocol::Times, GameHeader>(buffer, (int32)head->size));
        break;
    case Protocol::PLAYER_GOAL:
        HPlayerGoal(ref, ParsingPacket<Protocol::Player, GameHeader>(buffer, (int32)head->size));
        break;
    default:
        break;
    }
}

void GameHandler::HConnect(GameSessionRef& ref, Protocol::ConnectData&& pkt)
{
    if ((ref->_mySelf == nullptr) && ref->_room.expired())
        Ggames->DoAsync(&Games::EnterGame, ref, pkt.id(), pkt.room());
    //접속 시 전체 유저 정보 전달 -> 고민 이슈
}

void GameHandler::HPlayerMove(GameSessionRef& ref, Protocol::Move&& pkt)
{
    if (ref->_mySelf != nullptr) {
        if (auto room = ref->_room.lock()) {
            room->DoAsync(&Room::PlayerMove, pkt);
        }
    }
    else
    {
        ref->Disconnect(L"Player Move Disconnected");
    }
}

void GameHandler::HGameDrop(GameSessionRef& ref, Protocol::Move&& pkt)
{
    if ((ref->_mySelf != nullptr) && (pkt.id() == ref->_mySelf->GetId()))
    {
        cout << pkt.position().x() << " " << pkt.position().y()<< " " << pkt.position().z();
        ref->_room.lock()->DoAsync(&Room::PlayerDropSpawn, pkt.id());
    }
    else
    {
        ref->Disconnect(L"Drop Disconnected");
    }
}

void GameHandler::HTime(GameSessionRef& ref, Protocol::Times&& pkt)
{
    ref->Send(GameHandler::MakeSendBuffer(pkt, Protocol::TIME));
}

void GameHandler::HPlayerGoal(GameSessionRef& ref, Protocol::Player&& pkt)
{
    if (ref->_mySelf != nullptr) {
        if (auto room = ref->_room.lock())
            room->DoAsync(&Room::PlayerGoal, pkt);
    }
    else {
        ref->Disconnect(L"PlayerGoal Disconnected");
    }
}

SendBufferRef GameHandler::MakeSendBuffer(Protocol::ConnectData pkt, Protocol::INGAME type)
{
    return _MakeSendBuffer<Protocol::ConnectData, GameHeader, Protocol::INGAME>(pkt, type);
}
SendBufferRef GameHandler::MakeSendBuffer(Protocol::StartData pkt, Protocol::INGAME type)
{
    return _MakeSendBuffer<Protocol::StartData, GameHeader, Protocol::INGAME>(pkt, type);
}
SendBufferRef GameHandler::MakeSendBuffer(Protocol::MoveData pkt, Protocol::INGAME type)
{
    return _MakeSendBuffer<Protocol::MoveData, GameHeader, Protocol::INGAME>(pkt, type);
}
SendBufferRef GameHandler::MakeSendBuffer(Protocol::Move pkt, Protocol::INGAME type)
{
    return _MakeSendBuffer<Protocol::Move, GameHeader, Protocol::INGAME>(pkt, type);
} 

SendBufferRef GameHandler::MakeSendBuffer(Protocol::Player pkt, Protocol::INGAME type)
{
    return _MakeSendBuffer<Protocol::Player, GameHeader, Protocol::INGAME>(pkt, type);
}

SendBufferRef GameHandler::MakeSendBuffer(Protocol::Times pkt, Protocol::INGAME type)
{
    return _MakeSendBuffer<Protocol::Times, GameHeader, Protocol::INGAME>(pkt, type);
}

SendBufferRef GameHandler::MakeSendBuffer(Protocol::PlayerGoalData pkt, Protocol::INGAME type)
{
    return _MakeSendBuffer<Protocol::PlayerGoalData, GameHeader, Protocol::INGAME>(pkt, type);
}

SendBufferRef GameHandler::MakeSendBuffer(Protocol::SyncPlayer pkt, Protocol::INGAME type)
{
    return _MakeSendBuffer<Protocol::SyncPlayer, GameHeader, Protocol::INGAME>(pkt, type);
}
