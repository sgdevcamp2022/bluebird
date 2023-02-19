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
			if (room->_start)
				room->DoAsync(&Room::Disconnect, _mySelf->GetId());
			else
				room->DoAsync(&Room::Leave, _mySelf->GetId());
		}
	}
	_mySelf = nullptr;
}

void GameSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	GameHandler::HandlerPacket(static_pointer_cast<GameSession>(shared_from_this()), buffer, len);
}

void GameSession::OnSend(int32 len)
{

}
