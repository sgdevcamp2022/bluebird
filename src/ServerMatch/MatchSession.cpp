#include "pch.h"
#include "MatchSession.h"

void MatchSession::OnConnected()
{
    
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
