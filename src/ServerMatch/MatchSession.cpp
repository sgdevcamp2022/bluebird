#include "pch.h"
#include "MatchSession.h"
#include "MatchManager.h"

void MatchSession::OnConnected()
{
    cout << "Session Connected" << endl;
}

void MatchSession::OnDisconnected()
{
    cout << "SessionDisconnected" << endl;
}

void MatchSession::OnRecvPacket(BYTE* buffer, Match::Header&& head)
{
    PacketSessionRef match_ref = static_pointer_cast<PacketSession>(shared_from_this());
    PacketHandler::HandlerPacket(match_ref, buffer, std::move(head));
}

void MatchSession::OnSend(int32 len)
{

}
