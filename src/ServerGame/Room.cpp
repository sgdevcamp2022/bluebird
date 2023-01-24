#include "pch.h"
#include "Room.h"
#include "Creature.h"
#include "GameSession.h"
#include "PacketSession.h"

void Room::MatchEnter(vector<PlayerRef>* ref)
{
	for(auto _ref : *ref)
		_players[_ref->GetId()] = _ref;
}

void Room::GameEnter(GameSessionRef ref, int64 id)
{
	//확인 작업 필요
	_players[id]->SetOwner(ref);
	ref->_mySelf = _players[id];
}

void Room::ObstacleEnter(ObtacleRef obtacleRef)
{
	_obstacles[obtacleRef->GetId()] = obtacleRef;
}

void Room::Leave(PlayerRef ref)
{
	_players[ref->GetId()]->SetOwner(nullptr);
	_players.erase(ref->GetId());
}

void Room::PlayerMove(PlayerRef ref)
{
	_players[ref->GetId()]->MovePosition(ref->GetPosition());
	
}

void Room::ObstacleMove(int32 id, ObtacleRef ref)
{
	_obstacles[id] = ref;
}

void Room::Broadcast(SendBufferRef ref)
{
	for (auto& _ref : _players) {
		_ref.second->GetOwner()->Send(ref);
	}
}