#pragma once
#include <JobQueue.h>

class Room : public JobQueue
{
public:
	Room(int32 level, int32 room) : _mapLevel(level), _matchRoom(room) { }
	~Room() { cout << "게임 종료 " << _matchRoom << endl; }
	void MatchEnter(vector<PlayerRef>* ref);
	void GameEnter(GameSessionRef ref, int64 id);
	void ObstacleEnter(ObtacleRef obtacleRef);
	void Leave(PlayerRef ref);

	void PlayerMove(PlayerRef ref);
	void ObstacleMove(int32, ObtacleRef ref);
	void Broadcast(SendBufferRef ref);

private:
	int32					_matchRoom;
	int32					_mapLevel;
	Map<int64, PlayerRef>	_players;
	Map<int64, ObtacleRef>	_obstacles;
};