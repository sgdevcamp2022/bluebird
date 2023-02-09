#include "pch.h"
#include "MatchSession.h"
#include "MatchManager.h"

void MatchSession::OnConnected()
{
    cout << "Session Connected" << endl;
    GMatch->ConnectLobyServer(static_pointer_cast<MatchSession>(shared_from_this()));
}

void MatchSession::OnDisconnected()
{
    
}

void MatchSession::OnRecvPacket(BYTE* buffer, Match::Header&& head)
{
    PacketSessionRef match_ref = static_pointer_cast<PacketSession>(shared_from_this());
    PacketHandler::HandlerPacket(match_ref, buffer, std::move(head));
}

void MatchSession::OnSend(int32 len)
{

}
