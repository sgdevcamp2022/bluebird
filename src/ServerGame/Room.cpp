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
	_playerSize = ref.size();
	for (auto _ref : ref) {
		int64 id = _ref->GetId();
		_players[id] = _ref;
		_players[id]->SetPosition(_spawnPosition[id%15]);
	}
}

// 생성 후 유저 입장
void Room::GameEnter(GameSessionRef ref, int64 id)
{
	//확인 작업 필요
	auto player = _startData.add_player();
	
	if (TEST) {
		PlayerRef player = make_shared<Player>(id, _matchRoom, _spawnPosition[id % 15]);
		player->SetOwner(ref);

		_players[id] = player;
		ref->_mySelf = player;
		_playerSize += 1;
		cout << _playerSize << endl;
	}
	else if (_players.find(id) != _players.end()) {
		_players[id]->SetOwner(ref);
		ref->_mySelf = _players[id];
	}

	player->set_id(id);
	GameUtils::SetVector3(player->mutable_position(), _players[id]->GetPosition());
	GameUtils::SetVector3(player->mutable_rotation(), _players[id]->GetRotation());

	{
		Protocol::Player data;
		data.set_id(id);
		GameUtils::SetVector3(data.mutable_position(), _players[id]->GetPosition());
		GameUtils::SetVector3(data.mutable_rotation(), _players[id]->GetRotation());

		ref->Send(GameHandler::MakeSendBuffer(data, Protocol::CONNECT));
	}
}

void Room::ObstacleEnter(map<int64, ObtacleRef>* obtacles)
{
	_obstacles = *obtacles;

	//전체 플레이어에게 정보 전달 필요
	for(auto obta : _obstacles){
		auto ob = _startData.add_obtacle();
		ob->set_id(obta.first);
		ob->set_speed(obta.second->GetSpeed());
		ob->set_shape(obta.second->GetShape());
		cout << "Shape" << ob->shape() << endl;
		GameUtils::SetVector3(ob->mutable_position(), obta.second->GetPosition());
		GameUtils::SetVector3(ob->mutable_rotation(), obta.second->GetRotation());
	}
}

void Room::Leave(PlayerRef ref)
{
	_players[ref->GetId()]->SetOwner(nullptr);
	_players.erase(ref->GetId());

	Protocol::Data data;
	data.set_id(ref->GetId());
	data.set_matchroom(_matchRoom);
	data.set_maplevel(_mapLevel);

	_playerSize.fetch_sub(1);
	Broadcast(GameHandler::MakeSendBuffer(data, Protocol::LEAVE));
}

void Room::Start()
{
	//테스트 코드
	if (_start)
		return;
	if (_playerSize < START_COUNT || _startData.obtacle_size() == 0) {
		DoTimer(3000, &Room::Start);
		return;
	}
	vector<int64> keys;
	for (auto player : _players)
	{
		if (player.second->GetOwner() == nullptr) {
			keys.push_back(player.first);
			continue;
		}
	}
	for (auto key : keys)
	{
		_players.erase(key);
	}
	Broadcast(GameHandler::MakeSendBuffer(_startData, Protocol::START));

	_start.store(true);
	TimeSync();
}

void Room::PlayerMove(Protocol::Move data)
{
	//콘텐츠 구현
	//시뮬레이션 구현해야됨.
	auto point = data.position();

	cout << "Move(" << data.id() << ") : " << point.x() << " " << point.y() << " " << point.z() << endl;

	PlayerRef player = _players[data.id()];

	player->Move(data.position(), data.rotation());
	
	Broadcast(GameHandler::MakeSendBuffer(data, Protocol::PLAYER_MOVE));
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

void Room::ComplteGame(Protocol::Player player)
{
	_winnerId.push_back(player.id());
	//TODO 확인 작업 필요
	if (_winner.fetch_add(1) == WINNER1(_playerSize))
	{
		_start.store(false);
		//TODO 넘기는 작업 필요
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

bool Room::IsPlayer(int64 id)
{
	if (_players.find(id) != _players.end()) {
		if (_players[id]->GetOwner() == nullptr)
			true;
	}
	return false;
}
