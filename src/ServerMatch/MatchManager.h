#pragma once
#include <JobQueue.h>

class MatchManager : public JobQueue
{
public:
	MatchManager();
	~MatchManager();

	void MatchEnter(MatchSessionRef session, Match::Data data, PlayerRef player, int32 level);
	void MatchLeave(int64 id, int32 level, int32 room);
	void MatchPull(int32 level, int32 room);
	void SetService(ClientServiceRef ref);

private:
	vector<vector<MatchRoomRef>> _matchRooms;

	ClientServiceRef			_ref = nullptr;
	vector<int32>				_matchNums;
	Match::Users				_users;
};

extern shared_ptr<MatchManager> GMatch;