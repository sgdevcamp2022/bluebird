#pragma once
#include <JobQueue.h>

class Room : public JobQueue
{
public:
	Room(int32 level, int32 room);
	~Room() { cout << "게임 종료 " << _matchRoom << endl; }
	void MatchEnter(vector<PlayerRef> ref);
	void GameEnter(GameSessionRef ref, int64 id);
	void ObstacleEnter(map<int64, ObtacleRef>* obtacles);
	void Leave(PlayerRef ref);
	void Start();

	void PlayerMove(Protocol::Move data);
	void ObstacleMove(vector<Npc::Obstacle> datas);
	void ComplteGame(Protocol::Player);
	void Broadcast(SendBufferRef ref);
public:
	atomic<bool>			_start = true;

private:
	int32					_matchRoom;
	int32					_mapLevel;
	map<int64, PlayerRef>	_players;
	map<int64, ObtacleRef>	_obstacles;
	vector<Vector3>			_spawnPosition;
	vector<int64>			_winnerId;
	Protocol::Data			_startData;

private:
	atomic<int32>			_playerSize = 0;
	atomic<int32>			_winner = 0;
};