#pragma once
#include <JobQueue.h>

class MatchManager : public JobQueue
{
public:
	MatchManager();
	~MatchManager();

	void MatchEnter(MatchSessionRef session, PlayerRef player, int32 level);
	void MatchLeave(int64 id, int32 level, int32 room);
	void MatchPull(int32 level, int32 match, int32 room);
	void ConnectGameServer(ConnectSessionRef ref);
	void ConnectLobyServer(MatchSessionRef ref);

private:
	array<vector<int32>, 7>		_playerWait;
	//<int32>					_matchNums;
	atomic<int32>				_roomId = 0;

	ConnectSessionRef			_gameref = nullptr;
	MatchSessionRef				_lobyref = nullptr;
	Match::S_Match				_users;
};

extern shared_ptr<MatchManager> GMatch;