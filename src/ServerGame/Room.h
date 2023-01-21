#pragma once
#include <JobQueue.h>

class Player {
public:
	Player(uint32 id, uint32 mapLevel, Vector3 position)
		:_id(id), _mapLevel(mapLevel), _position(position) {}
	Player(uint32 id, uint32 mapLevel)
		:_id(id), _mapLevel(mapLevel) {}
	uint32			_id = 0;
	uint32			_mapLevel = 0;
	GameSessionRef	_ownerSession = nullptr;

	Vector3&		GetPosition() { return _position; }
	void			MovePosition(Vector3 position);

private:
	Vector3			_position;
	//¿òÁ÷ÀÓ ÆÄ¾Ç 
};

class Room : public JobQueue
{
public:
	void MatchEnter(vector<PlayerRef>* ref);
	void GameEnter(GameSessionRef ref, PlayerRef playerRef);

	void Leave(PlayerRef ref);
	void Move(PlayerRef ref);
	void Broadcast(SendBufferRef ref);

private:
	Map<uint32, PlayerRef> _players;
};

extern shared_ptr<Room> GRoom;