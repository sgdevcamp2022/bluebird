#pragma once
#include <JobQueue.h>

class MatchManager : public JobQueue
{
public:
	MatchManager();
	~MatchManager();

	void MatchEnter(PlayerRef player, int32 roomNum);
	void MatchLeave(PlayerRef player, int32 roomNum);
	void MatchPull(int32 roomNum);
	void SetService(ClientServiceRef ref);

private:
	vector<MatchRoomRef> _matchRooms;
	ClientServiceRef	_ref = nullptr;
	atomic<int32>		_matchNum = 0;
	Match::Users		_users;
};

extern shared_ptr<MatchManager> GMatch;