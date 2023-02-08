#include "pch.h"
#include "Games.h"
#include "Room.h"
#include <JobQueue.h>

shared_ptr<Games> Ggames = make_shared<Games>();

void Games::NewGame(vector<PlayerRef> players, int32 level, int32 room)
{
	_games[room] = make_shared<Room>(level, room);
	_games[room]->MatchEnter(std::move(players));
}

void Games::EnterGame(GameSessionRef session, int64 id, int32 room)
{
	//TODO 학인 절차
	
	//테스트 코드
	if (TEST)
	{
		if (!IsRoom(room)) {
			_games[room] = make_shared<Room>(2, room);
			session->_room = _games[room];
			_games[room]->GameEnter(session, id);
			DoTimer(5000, &Games::StartGame, room);

			auto _ref = GetNpcRef();
			if (_ref != nullptr) {
				Npc::LoginData data;
				data.set_maplevel(2);
				data.set_matchroom(0);

				_ref->Send(NpcHandler::MakeSendBuffer(data, Npc::LOGIN));
			}
			else {
				map<int64, ObtacleRef> input;
				input[0] = make_shared<Obtacle>(0, 0, 0, Vector3{ 5, 1, 1 }, Vector3{ 0,0,0 }, 10.0f);
				input[1] = make_shared<Obtacle>(1, 1, 0, Vector3{ 1, 1, 1 }, Vector3{ 0,0,0 }, 10.0f);
				_games[room]->ObstacleEnter(&input);
			}
		}
		else {
			session->_room = _games[room];
			_games[room]->GameEnter(session, id);
		}
	}
	else if (IsRoom(room)) {
		if (_games[room]->IsPlayer(id)) {
			session->_room = _games[room];
			_games[room]->GameEnter(session, id);
		}
		else {
			Protocol::Data data;
			data.set_id(-1);
			data.set_matchroom(room);
			session->Send(GameHandler::MakeSendBuffer(data, Protocol::CONNECT_FAIL));
		}
	}
	else {
		Protocol::Data data;
		data.set_id(id);
		data.set_matchroom(-1);
		session->Send(GameHandler::MakeSendBuffer(data, Protocol::CONNECT_FAIL));
	}
}

void Games::StartGame(int32 room)
{
	int check;
	if(check = _games[room]->Start() == -1)
		DoTimer(5000, &Games::StartGame, room);
	else if(GetNpcRef() != nullptr){
		Npc::StartData data;
		data.set_game(true);
		data.set_room(room);
		data.set_size(check);
		GetNpcRef()->Send(NpcHandler::MakeSendBuffer(data, Npc::START));
	}
	//게임 시작
}

void Games::EndGame()
{
	//TODO
}

bool Games::IsRoom(int64 id)
{
	if (_games.find(id) == _games.end())
		return false;
	return true;
}

void Games::SetNpcRef(NpcSessionRef ref)
{
	if (_npcRef == nullptr)
		_npcRef = ref;
}
