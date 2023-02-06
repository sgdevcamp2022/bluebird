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
	cout << "Comming" << endl;
	PacketSessionRef match_ref = static_pointer_cast<PacketSession>(shared_from_this());
	MatchHandler::HandlerPacket(match_ref, buffer, len);
}

void MatchSession::OnSend(int32 len)
{

}
