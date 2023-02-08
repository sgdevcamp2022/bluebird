#pragma once
#include <JobQueue.h>

class MatchRoom : public JobQueue
{
public:
	int32 Enter(PlayerRef player);
	void Leave(int64 id);
	void Broadcast(Match::Users& users, int32 matchRoom);

	void Clear() { _players.clear(); }
	int32 GetSize() { return static_cast<int32>(_players.size()); }
	
private:
	map<int64, PlayerRef> _players;
};