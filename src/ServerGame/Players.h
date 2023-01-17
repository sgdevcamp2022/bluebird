#pragma once
#include <JobQueue.h>

class Player {
public:
	Player(uint32 id, uint32 mapLevel, GameSessionRef owner)
		:_id(id), _mapLevel(mapLevel), _ownerSession(owner) {}

	uint32			_id = 0;
	uint32			_mapLevel = 0;
	GameSessionRef	_ownerSession = nullptr;
};

class Players : public JobQueue
{
public:
	void Enter(vector<PlayerRef>* ref);
	void Leave(PlayerRef ref);

private:
	Map<uint32, PlayerRef> _players;
};

extern shared_ptr<Players> GPlayers;