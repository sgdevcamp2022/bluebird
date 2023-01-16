#pragma once
#include <JobQueue.h>

class MatchManager : public JobQueue
{
public:
	MatchManager();
	~MatchManager();

	void MatchEnter(PlayerRef player, int32 roomNum);
	void MatchLeave(PlayerRef player, int32 roomNum);

private:
	vector<MatchRoomRef> _matchRooms;
};

extern shared_ptr<MatchManager> GMatch;