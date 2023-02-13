#include "pch.h"
#include "Room.h"
#include "GameObject.h"
#include "GameSession.h"
#include "PacketSession.h"

Room::Room(int32 level, int32 room) : _mapLevel(level), _matchRoom(room)
{
	_startData.set_matchroom(room);
	_startData.set_maplevel(level);

	CHECK = [=](int64 id) {
		if (_start && (_players[_stage].find(id) != _players[_stage].end()))
			return true;
		else
			return false;
	};
}

Room::~Room()
{
	_spawnPosition.clear();
	_obstacles.clear();
	for (int i = 0; i < _players.size();i++) {
		_players[i].clear();
	}
}

// 방 생성
void Room::MatchEnter(vector<PlayerRef> ref)
{
	for (auto _ref : ref) {
		int64 id = _ref->GetId();
		_players[_stage][id] = _ref;
	}
}

// 생성 후 유저 입장
void Room::GameEnter(GameSessionRef ref, int64 id)
{
	//확인 작업 필요
	cout << "Inside User" << endl;
	auto p = _startData.add_player();
	
	if (TEST) {
		PlayerRef player = make_shared<Player>(id, _matchRoom);
		player->SetOwner(ref);

		_players[_stage][id] = player;
		ref->_mySelf = player;
		_playerSize += 1;
	}
	else if (_players[_stage].find(id) != _players[_stage].end()) {
		_players[_stage][id]->SetOwner(ref);
		ref->_mySelf = _players[_stage][id];
		_playerSize += 1;
	}

	//내부에서 다 저장
	_players[_stage][id]->SetPlayer(p);
	//_players[_stage][id]->SetPosition(0.1f, 0.2f, 29.f);

	{
		Protocol::Player data;
		data.set_id(id);
		GameUtils::SetVector3(data.mutable_position(), _players[_stage][id]->GetPosition());
		GameUtils::SetVector3(data.mutable_rotation(), _players[_stage][id]->GetRotation());

		ref->Send(GameHandler::MakeSendBuffer(data, Protocol::CONNECT));
	}
}

void Room::ObstacleEnter(Npc::LoginData pkt)
{
	for (int i = 0; i < pkt.obstacle_size(); i++) {
		auto data = pkt.obstacle(i);
		auto ob = _startData.add_obtacle();

		if (data.has_position() && data.has_rotation()) {
			_obstacles[data.id()] = make_shared<Obtacle>(data.id(), data.shape(), pkt.matchroom(), data.speed(), data.direction());
			_obstacles[data.id()]->SetObstacle(ob);
			_obstacles[data.id()]->SetSpawnPoint(data.position(), data.rotation());
			ob->set_direction(_obstacles[data.id()]->GetDirection());
		}
	}
	for (int i = 0; i < pkt.spawn_size(); i++) {
		Npc::PlayerSpawn spawn = pkt.spawn(i);
		_spawnPosition.push_back({ spawn.position(), spawn.rotation() });
	}
	//전체 플레이어에게 정보 전달 필요
}

void Room::ReConnect(GameSessionRef ref, int64 id)
{
	// 정보 전체 전달
	// 나중에 고치기
	if (CHECK(id)) {
		cout << "ReConnect" << endl;
		_players[_stage][id]->SetOwner(ref);
		ref->_mySelf = _players[_stage][id];
		for (int i = 0; i < _startData.player_size(); i++) {
			auto player = _startData.player(i);
			cout << player.position().x() << " " << player.position().y() << " " << player.position().z();
		}
		ref->Send(GameHandler::MakeSendBuffer(_startData, Protocol::RECONNECT));
	}
}

void Room::Disconnect(PlayerRef ref)
{
	cout << "Disconncet" << endl;
	_players[_stage][ref->GetId()]->SetOwner(nullptr);
}

void Room::Leave(PlayerRef ref)
{
	_players[_stage][ref->GetId()]->SetOwner(nullptr);
	_players[_stage].erase(ref->GetId());

	Protocol::Data data;
	data.set_id(ref->GetId());
	data.set_matchroom(_matchRoom);
	data.set_maplevel(_mapLevel);

	_playerSize -= 1;
	Broadcast(GameHandler::MakeSendBuffer(data, Protocol::LEAVE));
}

int Room::Start()
{
	/*if (_playerSize < START_COUNT || _startData.obtacle_size() == 0) {
		return -1;
	}*/
	//테스트 코드
	if (_playerSize < START_COUNT) {
		return -1;
	}
	vector<int64> keys;
	for (auto& player : _players[_stage])
	{
		if (player.second->GetOwner() == nullptr) {
			keys.push_back(player.first);
			continue;
		}
		else {
			int32 id = player.second->GetId() % _spawnPosition.size();
			player.second->SetSpawnPoint(_spawnPosition[id].first, _spawnPosition[id].second);
		}
	}
	for (auto key : keys)
	{
		_players[_stage].erase(key);
	}

	Broadcast(GameHandler::MakeSendBuffer(_startData, Protocol::START));

	_start.store(true);
	TimeSync();

	return _players[_stage].size();
}

void Room::PlayerMove(Protocol::Move data)
{
	//콘텐츠 구현
	//시뮬레이션 구현해야됨.
	if (CHECK(data.id())) {
		// 추가 구현 방식 생각 해보기
		auto point = data.position();
		PlayerRef player = _players[_stage][data.id()];

		if (point.y() > 0.f) {
			cout << "Move(" << data.id() << ") : " << point.x() << " " << point.y() << " " << point.z() << endl;

			player->Move(data.position(), data.rotation());
			Broadcast(GameHandler::MakeSendBuffer(data, Protocol::PLAYER_MOVE));
		}
		else if (player->GetMoveRight()) {
			cout << "DROP" << endl;
			player->SetSpawnPoint(_spawnPosition[0].first, _spawnPosition[0].second);
			player->MoveChange();
			Broadcast(GameHandler::MakeSendBuffer(data, Protocol::PLAYER_DROP));
		}
	}
}

void Room::ObstacleMove(int64 id, Npc::Vector3 position, Npc::Vector3 rotation, Protocol::Move data)
{
	if (_start) {
		if (_obstacles.find(id) != _obstacles.end()) {
			_obstacles[id]->Move(position, rotation);
			cout << "Object 이동" << endl;
			GameUtils::SetVector3(data.mutable_position(), _obstacles[id]->GetPosition());
			GameUtils::SetVector3(data.mutable_rotation(), _obstacles[id]->GetRotation());
		}

		Broadcast(GameHandler::MakeSendBuffer(data, Protocol::OBSTACLE_MOVE));
	}
}

void Room::PlayerGoal(Protocol::Player data)
{
	if (CHECK(data.id())) {
		cout << "Input goal" << endl;
		PlayerRef player = _players[_stage][data.id()];
		_players[_stage + 1][player->GetId()] = player;
		//TODO 확인 작업 필요
		//if (_winner.fetch_add(1) == WINNER1(_playerSize))
		if (_players[_stage + 1].size() == GOAL_COUNT)
		{
			_start.store(false);
			//TODO 넘기는 작업 필요
			NextStage();
		}
		else {
			Protocol::PlayerGoalData data;
			data.set_id(data.id());
			data.set_success(true);

			Broadcast(GameHandler::MakeSendBuffer(data, Protocol::PLAYER_GOAL));
		}
	}
}

void Room::TimeSync()
{
	if (_start) {
		Protocol::Times time;
		time.set_time(GetTickCount64());
		cout << time.time() << endl;

		Broadcast(GameHandler::MakeSendBuffer(time, Protocol::GET_TICK));
	}
	else
		DoTimer(60000, &Room::TimeSync);
}

void Room::Broadcast(SendBufferRef ref)
{
	for (auto& _ref : _players[_stage]) {
		if(_ref.second->GetOwner() != nullptr)
			_ref.second->GetOwner()->Send(ref);
	}
}

void Room::NextStage()
{
	cout << "Game End" << endl;
	int32 past = _stage.fetch_add(1);
	Protocol::PlayerGoalData data;
	_startData.Clear();
	for (auto& _ref : _players[past]) {
		if (_players[_stage].find(_ref.first) == _players[_stage].end()) {
			data.set_id(_ref.first);
			data.set_success(false);
			_ref.second->GetOwner()->Send(GameHandler::MakeSendBuffer(data, Protocol::GAME_FAIL));
		}
		else
		{
			_players[_stage][_ref.first]->SetPlayer(_startData.add_player());
			data.set_id(_ref.first);
			data.set_success(true);
			_ref.second->GetOwner()->Send(GameHandler::MakeSendBuffer(data, Protocol::GAME_COMPLTE));
		}
	}
	_playerSize = _players[_stage].size();
	_players[past].clear();

	if (_stage == MAX_STAGE)
		RoomEnd();
	else
		Ggames->DoAsync(&Games::NextStageGame, _matchRoom, _mapLevel, _stage.load());
}

void Room::RoomEnd()
{
	//TODO 정리하기
	Ggames->EndGame(_matchRoom, _mapLevel);
}

bool Room::IsPlayer(int64 id)
{
	if (_players[_stage].find(id) != _players[_stage].end()) 
	{
		if (_players[_stage][id]->GetOwner() == nullptr) 
		{
			return true;
		}
	}
	return false;
}
