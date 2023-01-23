#include "pch.h"
#include "NpcSession.h"
#include "NpcHandler.h"

void NpcSession::OnConnected()
{
}

void NpcSession::OnDisconnected()
{
}

void NpcSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketSessionRef match_ref = static_pointer_cast<PacketSession>(shared_from_this());
	NpcHandler::HandlerPacket(match_ref, buffer, len);
}

void NpcSession::OnSend(int32 len)
{
}
