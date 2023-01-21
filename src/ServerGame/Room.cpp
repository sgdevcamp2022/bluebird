#include "pch.h"
#include "Room.h"
#include "GameSession.h"
#include "PacketSession.h"

shared_ptr<Room> GRoom = make_shared<Room>();

void Room::MatchEnter(vector<PlayerRef>* ref)
{
	for(auto _ref : *ref)
		_players[_ref->_id] = _ref;
}

void Room::GameEnter(GameSessionRef ref, PlayerRef playerRef)
{
	_players[playerRef->_id] = playerRef;
}

void Room::Leave(PlayerRef ref)
{
	_players.erase(ref->_id);
}

void Room::Move(PlayerRef ref)
{
	_players[ref->_id]->MovePosition(ref->GetPosition());
	
}

void Room::Broadcast(SendBufferRef ref)
{
	for (auto& _ref : _players) {
		_ref.second->_ownerSession->Send(ref);
	}
}

void Player::MovePosition(Vector3 position)
{
	//이동 체크
	_position.x = position.x;
	_position.y = position.y;
	_position.z = position.z;
}
