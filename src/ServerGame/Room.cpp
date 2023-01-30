#include "pch.h"
#include "Room.h"
#include "GameObject.h"
#include "GameSession.h"
#include "PacketSession.h"

Room::Room(int32 level, int32 room) : _mapLevel(level), _matchRoom(room)
{
	for (int i = 0; i < 15; i++)
	{
		_spawnPosition.push_back(Vector3{ (float)i, (float)i, (float)i });
	}
}

// 방 생성
void Room::MatchEnter(vector<PlayerRef> ref)
{
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
	Vector3 position(_players[id]->GetPosition());

	player->set_id(id);
	player->set_x(position.x);
	player->set_y(position.y);
	player->set_z(position.z);

	_players[id]->SetOwner(ref);
	ref->_mySelf = _players[id];

	{
		Protocol::Data data;
		data.set_id(id);
		auto p = data.add_player();
		p = player;

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
		ob->set_shape(obta.second->GetShape());
		ob->set_x(obta.second->GetPosition().x);
		ob->set_y(obta.second->GetPosition().y);
		ob->set_z(obta.second->GetPosition().z);
	}
	_startData.set_matchroom(_matchRoom);

	//Broadcast(GameHandler::MakeSendBuffer(data, Protocol::OBSTACLE_SETTING));
}

void Room::Leave(PlayerRef ref)
{
	_players[ref->GetId()]->SetOwner(nullptr);
	_players.erase(ref->GetId());
}

void Room::Start()
{
	/*if (_obstacles.size() == 0) {
		DoTimer(3000, &Room::Start);
	}*/
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
}

void Room::PlayerMove(Protocol::Data data)
{
	//콘텐츠 구현
	auto point = data.player(0);

	cout << "Move(" << data.id() << ") : " << point.x() << " " << point.y() << " " << point.z() << endl;

	PlayerRef player = _players[data.id()];

	player->MovePosition(Vector3(point));
	
	cout << "BroadCast" << endl;
	Broadcast(GameHandler::MakeSendBuffer(data, Protocol::MOVE));
}

void Room::ObstacleMove(vector<Npc::Obstacle> datas)
{
	Protocol::Data data;
	for (int i = 0; i < datas.size(); i++) {
		Vector3 position(datas[i]);
		if (_obstacles.find(datas[i].id()) != _obstacles.end()) {
			_obstacles[datas[i].id()]->MovePosition(std::move(position));
			auto ob = data.add_obtacle();

			ob->set_id(datas[i].id());
			ob->set_x(position.x);
			ob->set_y(position.y);
			ob->set_z(position.z);
		}
	}
	Broadcast(GameHandler::MakeSendBuffer(data, Protocol::OBSTACLE_MOVE));
}

void Room::Broadcast(SendBufferRef ref)
{
	for (auto& _ref : _players) {
		if(_ref.second->GetOwner() != nullptr)
			_ref.second->GetOwner()->Send(ref);
	}
}