#pragma once
#include <JobQueue.h>

class MatchRoom
{
public:
	int Enter(PlayerRef player);
	void Leave(PlayerRef player);
	void Broadcast(ClientServiceRef&);

	void Clear() { _players.clear(); }
	int32 GetSize() { return _players.size(); }

private:
	map<uint64, PlayerRef> _players;
};