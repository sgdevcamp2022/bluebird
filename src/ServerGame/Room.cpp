#include "pch.h"
#include "Room.h"
#include "GameObject.h"
#include "GameSession.h"
#include "PacketSession.h"

Room::Room(int32 level, int32 room) : _mapLevel(level), _matchRoom(room)
{
	for (int i = 1; i <= 15; i++)
	{
		_spawnPosition.push_back(Vector3{ (float)i, 1, (float)i });
	}
	_startData.set_matchroom(room);
	_startData.set_maplevel(level);
}

// 방 생성
void Room::MatchEnter(vector<PlayerRef> ref)
{
	for (auto _ref : ref) {
		int64 id = _ref->GetId();
		_players[id] = _ref;
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

		_players[id] = player;
		ref->_mySelf = player;
		_playerSize += 1;
	}
	else if (_players.find(id) != _players.end()) {
		_players[id]->SetOwner(ref);
		ref->_mySelf = _players[id];
		_playerSize += 1;
	}

	//내부에서 다 저장
	_players[id]->SetPlayer(p);
	_players[id]->SetPosition(0.1f, 0.2f, 29.f);

	{
		Protocol::Player data;
		data.set_id(id);
		GameUtils::SetVector3(data.mutable_position(), _players[id]->GetPosition());
		GameUtils::SetVector3(data.mutable_rotation(), _players[id]->GetRotation());

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
			_obstacles[data.id()]->SetPosition(data.position().x(), data.position().y(), data.position().z());
			ob->set_direction(_obstacles[data.id()]->GetDirection());
		}
	}
	//전체 플레이어에게 정보 전달 필요
}

void Room::ReConnect(GameSessionRef ref, int64 id)
{
	// 정보 전체 전달
	// 나중에 고치기
	cout << "ReConnect" << endl;
	_players[id]->SetOwner(ref);
	ref->_mySelf = _players[id];
	ref->_start = true;
	for (int i = 0; i < _startData.player_size(); i++) {
		auto player = _startData.player(i);
		cout << player.position().x() << " " << player.position().y() << " " << player.position().z();
	}
	ref->Send(GameHandler::MakeSendBuffer(_startData, Protocol::RECONNECT));
}

void Room::Disconnect(PlayerRef ref)
{
	cout << "Disconncet" << endl;
	_players[ref->GetId()]->SetOwner(nullptr);
}

void Room::Leave(PlayerRef ref)
{
	_players[ref->GetId()]->SetOwner(nullptr);
	_players.erase(ref->GetId());

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
	for (auto& player : _players)
	{
		if (player.second->GetOwner() == nullptr) {
			keys.push_back(player.first);
			continue;
		}
		else {
			player.second->GetOwner()->_start = true;
		}
	}
	for (auto key : keys)
	{
		_players.erase(key);
	}
	Broadcast(GameHandler::MakeSendBuffer(_startData, Protocol::START));

	_start.store(true);
	TimeSync();

	return _players.size();
}

void Room::PlayerMove(Protocol::Move data)
{
	//콘텐츠 구현
	//시뮬레이션 구현해야됨.
	auto point = data.position();
	PlayerRef player = _players[data.id()];
	
	if (point.y() > 0.f) {
		cout << "Move(" << data.id() << ") : " << point.x() << " " << point.y() << " " << point.z() << endl;
		
		player->Move(data.position(), data.rotation());
		Broadcast(GameHandler::MakeSendBuffer(data, Protocol::PLAYER_MOVE));
	}
	else if(player->GetMoveRight()){
		cout << "DROP" << endl;
		player->SetPosition(0.1f, 0.2f, 29.f);
		player->MoveChange();
		Broadcast(GameHandler::MakeSendBuffer(data, Protocol::PLAYER_DROP));
	}
}

void Room::ObstacleMove(int64 id, Npc::Vector3 position, Npc::Vector3 rotation, Protocol::Move data)
{
	if (_obstacles.find(id) != _obstacles.end()) {
		_obstacles[id]->Move(position, rotation);
		cout << "Object 이동" << endl;
		GameUtils::SetVector3(data.mutable_position(), _obstacles[id]->GetPosition());
		GameUtils::SetVector3(data.mutable_rotation(), _obstacles[id]->GetRotation());
	}
	
	Broadcast(GameHandler::MakeSendBuffer(data, Protocol::OBSTACLE_MOVE));
}

void Room::PlayerGoal(Protocol::Player data)
{
	cout << "Input goal" << endl;
	_winnerId.push_back(data.id());
	//TODO 확인 작업 필요
	//if (_winner.fetch_add(1) == WINNER1(_playerSize))
	if (_winnerId.size() == GOAL_COUNT)
	{
		_start.store(false);
		//TODO 넘기는 작업 필요
		GameEnd();
	}
	else {
		auto player = _winner.add_data();
		player->set_id(data.id());
		player->set_success(true);
		Broadcast(GameHandler::MakeSendBuffer(*player, Protocol::PLAYER_GOAL));
	}
}

void Room::TimeSync()
{
	Protocol::Times time;
	time.set_time(GetTickCount64());
	cout << time.time() << endl;

	Broadcast(GameHandler::MakeSendBuffer(time, Protocol::GET_TICK));

	DoTimer(60000, &Room::TimeSync);
}

void Room::Broadcast(SendBufferRef ref)
{
	for (auto& _ref : _players) {
		if(_ref.second->GetOwner() != nullptr)
			_ref.second->GetOwner()->Send(ref);
	}
}

void Room::GameEnd()
{
	cout << "Game End" << endl;
	for (auto& _ref : _players) {
		_ref.second->GetOwner()->_mySelf = nullptr;
		_ref.second->SetOwner(nullptr);
	}

	Broadcast(GameHandler::MakeSendBuffer(_winner, Protocol::GAME_COMPLTE));
	//TODO 넘겨주기

	_players.clear();
}

bool Room::IsPlayer(int64 id)
{
	if (_players.find(id) != _players.end()) 
	{
		if (_players[id]->GetOwner() == nullptr) 
		{
			return true;
		}
	}
	return false;
}
