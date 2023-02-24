#include "pch.h"
#include "Room.h"
#include "GameObject.h"
#include "GameSession.h"
#include "PacketSession.h"

Room::Room(int32 level, int32 room) : _mapLevel(level), _matchRoom(room)
{
	CHECK = [=](int64 id) {
		if (_start && (_players[_stage].find(id) != _players[_stage].end()))
			return true;
		else
			return false;
	};
	if (NPC_TEST) {
		Npc::Vector3 data;
		data.set_x(0.f);
		data.set_y(0.1f);
		data.set_z(30.f);

		_spawnPosition.push_back({ data, data });
		_spawnPosition.push_back({ data, data });
		_spawnPosition.push_back({ data, data });
	}
	_syncObstacle = new Protocol::SyncObstacle;
	_syncPlayer = new Protocol::SyncPlayer;
}

Room::~Room()
{
	RoomClear();
	cout << "Room Clear" << endl;

	delete _syncPlayer;
	delete _syncObstacle;
}

void Room::RoomClear()
{
	_spawnPosition.clear();
	_obstacles.clear();
	for (int i = 0; i < _players.size(); i++) {
		_players[i].clear();
	}
	_syncPlayer->Clear();
	_syncObstacle->Clear();
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
	auto p = _syncPlayer->add_player();
	
	if (CLIENT_TEST) {
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

	{
		Protocol::Player data;
		data.set_id(id);

		ref->Send(GameHandler::MakeSendBuffer(data, Protocol::CONNECT));
	}
}

void Room::ObstacleEnter(Npc::LoginData pkt)
{
	_syncObstacle->clear_obstacle();

	for (int i = 0; i < pkt.obstacle_size(); i++) {
		auto data = pkt.obstacle(i);
		auto ob = _syncObstacle->add_obstacle();

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
	cout << _obstacles.size() << " " << _spawnPosition.size() << endl;
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
		for (int i = 0; i < _syncPlayer->player_size(); i++) {
			auto player = _syncPlayer->player(i);
			cout << player.position().x() << " " << player.position().y() << " " << player.position().z();
		}
		{
			Protocol::StartData data;
			data.set_allocated_obstacles(_syncObstacle);
			data.set_allocated_players(_syncPlayer);
			ref->Send(GameHandler::MakeSendBuffer(data, Protocol::RECONNECT));

			data.release_obstacles();
			data.release_players();
		}
	}
}

void Room::Disconnect(int64 id)
{
	cout << "Disconncet " << id << endl;
	_players[_stage][id]->SetOwner(nullptr);

	if (_start)
	{
		_remainUser -= 1;
		if (_remainUser <= 0) {
			RoomEnd();
		}
	}
}

void Room::Leave(int64 id)
{
	cout << "Leave " << id << endl;
	_players[_stage].erase(id);

	Protocol::ConnectData data;
	data.set_id(id);
	data.set_room(_matchRoom);
	data.set_level(_mapLevel);

	Broadcast(GameHandler::MakeSendBuffer(data, Protocol::LEAVE));
	_playerSize -= 1;

	if (_start)
	{
		_remainUser -= 1;
		if (_remainUser <= 0) {
			RoomEnd();
		}
	}
}

void Room::Start()
{
	if (_playerSize < Solo_Start(_stage.load()) && !_start.load()) 
	{
		cout << "Start Fail " << _playerSize << endl;
		DoTimer(3000, &Room::Start);
	}
	else {
		if (Ggames->GetNpcRef() != nullptr)
		{
			Npc::StartData data;
			data.set_game(true);
			data.set_room(_matchRoom);
			data.set_size(_playerSize);
			Ggames->GetNpcRef()->Send(NpcHandler::MakeSendBuffer(data, Npc::START));
		}

		vector<int64> keys;
		int i = 0;
		for (auto& player : _players[_stage])
		{
			if (player.second->GetOwner() == nullptr) {
				keys.push_back(player.first);
				continue;
			}
			else {
				player.second->SetSpawnPoint(_spawnPosition[i].first, _spawnPosition[i].second);
				i = (i + 1) % _spawnPosition.size();
			}
		}
		for (auto key : keys)
		{
			_players[_stage].erase(key);
		}

		{
			Protocol::StartData data;
			data.set_allocated_obstacles(_syncObstacle);
			data.set_allocated_players(_syncPlayer);
			Broadcast(GameHandler::MakeSendBuffer(data, Protocol::START));

			data.release_obstacles();
			data.release_players();

		}
		_remainUser = _playerSize;
		_start.store(true);
		//Sync
		//TimeSync();

		_syncMove.set_time(GetTickCount64());
		GameSync();
	}
}

void Room::PlayerMove(Protocol::Move data)
{
	//콘텐츠 구현
	//시뮬레이션 구현해야됨.
	if (CHECK(data.id())) {
		// 추가 구현 방식 생각 해보기
		auto point = data.position();
		PlayerRef player = _players[_stage][data.id()];
		if (player->GetOwner() != nullptr) {
			if (point.y() > -10.0f) {

				_syncMove.add_move()->CopyFrom(data);

				player->Move(data.position(), data.rotation());
			}
			else if (player->GetMoveRight()) {
				cout << "DROP" << endl;
				player->SetSpawnPoint(_spawnPosition[0].first, _spawnPosition[0].second);
				player->MoveChange();
				GameUtils::SetVector3(data.mutable_position(), _spawnPosition[0].first);
				GameUtils::SetVector3(data.mutable_rotation(), _spawnPosition[0].second);
				Broadcast(GameHandler::MakeSendBuffer(data, Protocol::PLAYER_DROP));
			}
		}
	}
	else 
	{
		cout << "Something is wrong" << endl;
	}
}

void Room::ObstacleMove(int64 id, Npc::Vector3 position, Npc::Vector3 rotation, Protocol::Move data)
{
	if (_start) {
		if (_obstacles.find(id) != _obstacles.end()) {
			cout << "OBstacle Move " << id << endl;
			_obstacles[id]->Move(position, rotation);
			GameUtils::SetVector3(data.mutable_position(), _obstacles[id]->GetPosition());
			GameUtils::SetVector3(data.mutable_rotation(), _obstacles[id]->GetRotation());
		}
		Broadcast(GameHandler::MakeSendBuffer(data, Protocol::OBSTACLE_MOVE));
	}
}

void Room::PlayerDropSpawn(int64 id)
{
	_players[_stage][id]->MoveChange();
}

void Room::PlayerGoal(Protocol::Player data)
{
	if (CHECK(data.id())) {
		cout << "Input goal " << data.id() << endl;
		_players[NEXT_STAGE(_stage)][data.id()] = _players[_stage][data.id()];

		if (_players[NEXT_STAGE(_stage)].size() == Solo_Goal(_stage.load()))
		{
			cout << Solo_Goal(_stage.load());
			_start.store(false);
			//TODO 넘기는 작업 필요
			DoAsync(&Room::NextStage);
		}
		else 
		{
			Protocol::PlayerGoalData send;
			send.set_id(data.id());
			send.set_success(true);

			Broadcast(GameHandler::MakeSendBuffer(send, Protocol::PLAYER_GOAL));
		}
	}
}

void Room::TimeSync()
{
	Protocol::Times time;
	time.set_time(GetTickCount64());

	Broadcast(GameHandler::MakeSendBuffer(time, Protocol::GET_TICK));
	DoTimer(60000, &Room::TimeSync);
}

void Room::GameSync()
{
	if (_start) {
		//동기화 테스트
		if (_syncMove.move_size() > 0) {
			Broadcast(GameHandler::MakeSendBuffer(_syncMove, Protocol::PLAYER_SYNC));
			_syncMove.Clear();
		}
		_syncMove.set_time(GetTickCount64());

		DoTimer(50, &Room::GameSync);
	}
}

void Room::Broadcast(SendBufferRef ref)
{
	for (auto& _ref : _players[_stage]) {
		if (_ref.second->GetOwner() != nullptr) {
			_ref.second->GetOwner()->Send(ref);
		}
	}
}

void Room::NextStage()
{
	if(!NPC_TEST)
		_spawnPosition.clear();

	int32 past = _stage.fetch_add(1);
	Protocol::PlayerGoalData data;

	// 종료 후 유저들에게 정보 전달
	_syncPlayer->Clear();

	for (auto& _ref : _players[past]) {
		if (_players[_stage].find(_ref.first) == _players[_stage].end()) {
			data.set_id(_ref.first);
			data.set_success(false);
		}
		else
		{
			_players[_stage][_ref.first]->SetPlayer(_syncPlayer->add_player());
			data.set_id(_ref.first);
			data.set_success(true);
		}

		if (Last_Stage(_stage)) 
		{
			cout << "GameEnd "<< _ref.first << endl;
			if (_ref.second->GetOwner() != nullptr)
				_ref.second->GetOwner()->Send(GameHandler::MakeSendBuffer(data, Protocol::GAME_END));
		}
		else 
		{
			cout << "Game Complte " << _ref.first << endl;
			if (_ref.second->GetOwner() != nullptr)
				_ref.second->GetOwner()->Send(GameHandler::MakeSendBuffer(data, Protocol::GAME_COMPLTE));

			if (!data.success())
			{
				if (_ref.second->GetOwner() != nullptr)
					_ref.second->GetOwner()->_mySelf = nullptr;
				_ref.second->SetOwner(nullptr);
			}
		}
	}

	// 다음 스테이지로 넘어가기 위한 정리
	_playerSize = _players[_stage].size();
	cout << "Next Stage : " << _stage << endl;
	_obstacles.clear();
	_players[past].clear();

	// 마지막 스테이지 일 경우는 방 종료 아니면 다음 게임 진행.
	if (Last_Stage(_stage))
		DoAsync(&Room::RoomEnd);
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
