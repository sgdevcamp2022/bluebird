#include "pch.h"
#include "MatchSession.h"

void MatchSession::OnConnected()
{
    Protocol::S_DATA pkt;
    pkt.set_id(1);
    pkt.set_maplevel(2);
    pkt.set_matchroom(10);
    SendBufferRef ref = PacketHandler::MakeSendBuffer(pkt, Protocol::MATCH_LOGIN);

    Send(ref);
}

void MatchSession::OnDisconnected()
{
    
}

void MatchSession::OnRecvPacket(BYTE* buffer, int32 len)
{
    SessionRef game_ref = static_pointer_cast<Session>(shared_from_this());
    PacketHandler::HandlerPacket(game_ref, buffer, len);
}

void MatchSession::OnSend(int32 len)
{

}
