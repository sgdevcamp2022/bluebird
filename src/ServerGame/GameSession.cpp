#include "pch.h"
#include "GameSession.h"
#include "Room.h"

void GameSession::OnConnected()
{	

}

void GameSession::OnDisconnected()
{
	if (_mySelf != nullptr) {
		if (auto room = _room.lock()) {
			room->DoAsync(&Room::Leave, _mySelf);
		}
	}

	_mySelf = nullptr;
}

void GameSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketSessionRef match_ref = static_pointer_cast<PacketSession>(shared_from_this());
	GameHandler::HandlerPacket(match_ref, buffer, len);
}

void GameSession::OnSend(int32 len)
{

}
