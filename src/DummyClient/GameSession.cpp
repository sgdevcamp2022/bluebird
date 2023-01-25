#include "pch.h"
#include "GameSession.h"
#include "GameHandler.h"

void GameSession::OnConnected()
{
    static atomic<int> th(0);
    int id = th.fetch_add(1);
    {
        Protocol::Data pkt;
        pkt.set_id(id);
        pkt.set_maplevel(2);
        pkt.set_matchroom(0);
        auto ref = GameHandler::MakeSendBuffer(pkt, Protocol::CONNECT);
        Send(ref);
    }
    {
        Protocol::Data pkt;
        pkt.set_id(id);
        pkt.set_maplevel(2);
        pkt.set_matchroom(0);
        auto player = pkt.add_player();
        player->set_x(0.0f);
        player->set_y(0.0f);
        player->set_z(0.0f);
        auto ref = GameHandler::MakeSendBuffer(pkt, Protocol::MOVE);
        Send(ref);
    }
}

void GameSession::OnDisconnected()
{

}

void GameSession::OnRecvPacket(BYTE* buffer, int32 len)
{
    PacketSessionRef game_ref = static_pointer_cast<PacketSession>(shared_from_this());
    GameHandler::HandlerPacket(game_ref, buffer, len);
}

void GameSession::OnSend(int32 len)
{

}
