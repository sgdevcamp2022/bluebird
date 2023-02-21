#pragma once
#include <JobQueue.h>

class MatchManager : public JobQueue
{
public:
	MatchManager();
	~MatchManager();

	void MatchEnter(int64 id, int32 level);
	void MatchLeave(int64 id, int32 level, int32 room);

	int32 PlayerInsideMatch(PlayerLevel level, int32 id);
	void PlayerOutputMatch(array<PlayerLevel, 3> levels, int32 min, int32 max);

	void ConnectGameServer(ConnectSessionRef ref);
	void ConnectMatchServer(MatchSessionRef ref);
	void ConnectLobyServer(MatchSessionRef ref);

private:
	array<deque<int32>, 8>		_playerWait;
	map<int32, atomic<int32>>	_playerSize;

	atomic<int32>				_roomId = 1;

	ConnectSessionRef			_gameref = nullptr;
	MatchSessionRef				_lobyref = nullptr;
	MatchSessionRef				_matchref = nullptr;
};

extern shared_ptr<MatchManager> GMatch;