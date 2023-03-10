#pragma once
#include <JobQueue.h>

class Room : public JobQueue
{
public:
	Room(int32 level, int32 room);
	virtual ~Room();

	void RoomClear();
	void MatchEnter(vector<PlayerRef> ref);
	void GameEnter(GameSessionRef ref, int64 id);
	void ObstacleEnter(Npc::LoginData pkt);

	void ReConnect(GameSessionRef ref, int64 id);
	void Disconnect(int64 id);
	void Leave(int64 id);
	void Start();

	void PlayerMove(Protocol::Move data);
	void ObstacleMove(int64 id, Npc::Vector3 position, Npc::Vector3 rotation, Protocol::Move data);
	void PlayerDropSpawn(int64 id);
	void TimeSync();

	void GameSync();
	void Broadcast(SendBufferRef ref);

	// 다음 스테이지 넘기기
	void PlayerGoal(Protocol::Player data);
	void NextStage();

	// 스테이지 및 방 종료
	void RoomEnd();

	// 나중에 바꾸기
	bool IsPlayer(int64 id);

public:
	atomic<bool>				_start = false;
	atomic<int32>				_stage = 1;

private:
	int32						_matchRoom;
	int32						_mapLevel;
	
	Protocol::SyncObstacle*		_syncObstacle;
	Protocol::SyncPlayer*		_syncPlayer;
	int32						_playerSize = 0;
	int32						_remainUser = 0;

	array<map<int64, PlayerRef>, 4>		_players;
	map<int64, ObtacleRef>				_obstacles;
	Protocol::MoveData _syncMove;
	vector<pair<Npc::Vector3, Npc::Vector3>>	_spawnPosition;

	function<bool(int64 id)> CHECK;
};