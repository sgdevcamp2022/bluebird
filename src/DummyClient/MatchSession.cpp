#include "pch.h"
#include "MatchSession.h"

void MatchSession::OnConnected()
{
    static atomic<int> th(0);
    Match::Data pkt;
    pkt.set_id(th.fetch_add(1));
    pkt.set_maplevel(2);
    pkt.set_state(false);
    auto ref = PacketHandler::MakeSendBuffer(pkt, Match::C_LOGIN);
    Send(ref);

    /*ref = PacketHandler::MakeSendBuffer(pkt, Match::C_CANCLE);
    Send(ref);*/

}

void MatchSession::OnDisconnected()
{
   
}

void MatchSession::OnRecvPacket(BYTE* buffer, int32 len)
{
    PacketSessionRef game_ref = static_pointer_cast<PacketSession>(shared_from_this());
    PacketHandler::HandlerPacket(game_ref, buffer, len);
}

void MatchSession::OnSend(int32 len)
{

}
