#pragma once
#include <JobQueue.h>

class Room : public JobQueue
{
public:
	Room(int32 level, int32 room) : _mapLevel(level), _matchRoom(room) { }
	~Room() { cout << "게임 종료 " << _matchRoom << endl; }
	void MatchEnter(vector<PlayerRef>* ref);
	void GameEnter(GameSessionRef ref, int64 id);
	void ObstacleEnter(map<int64, ObtacleRef>* obtacles);
	void Leave(PlayerRef ref);

	void PlayerMove(Protocol::Data data);
	void ObstacleMove(int64 id, Vector3 position);
	void Broadcast(SendBufferRef ref);
public:
	atomic<bool>			_start = true;

private:
	int32					_matchRoom;
	int32					_mapLevel;
	map<int64, PlayerRef>	_players;
	map<int64, ObtacleRef>	_obstacles;
	
};