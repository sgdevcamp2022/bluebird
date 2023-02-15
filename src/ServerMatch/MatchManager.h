#pragma once
#include <JobQueue.h>

using InFun = function<int32(int32)>;
using OutFn = function<void(Match::S_Match&, array<PlayerLevel,3>, int32, int32)>;

class MatchManager : public JobQueue
{
public:
	MatchManager();
	~MatchManager();

	void MatchEnter(int64 id, int32 level);
	void MatchLeave(int64 id, int32 level, int32 room);
	void MatchPull(int32 level);

	void ConnectGameServer(ConnectSessionRef ref);
	void ConnectMatchServer(MatchSessionRef ref);
	void ConnectLobyServer(MatchSessionRef ref);

private:
	array<deque<int32>, 8>		_playerWait;
	map<int32, int32>			_playerSize;

	array<InFun, 8>				_playerCount;
	OutFn						_playerOut;

	atomic<int32>				_roomId = 1;

	ConnectSessionRef			_gameref = nullptr;
	MatchSessionRef				_lobyref = nullptr;
	MatchSessionRef				_matchref = nullptr;

private:

};

extern shared_ptr<MatchManager> GMatch;