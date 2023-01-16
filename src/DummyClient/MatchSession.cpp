#include "pch.h"
#include "MatchSession.h"

void MatchSession::OnConnected()
{
    static atomic<int> th(0);
    Protocol::S_DATA pkt;
    pkt.set_id(th.fetch_add(1));
    pkt.set_maplevel(2);
    pkt.set_matchroom(1);
    SendBufferRef ref = PacketHandler::MakeSendBuffer(pkt, Protocol::C_LOGIN);

    Send(ref);
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
