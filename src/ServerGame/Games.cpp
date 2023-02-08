#include "pch.h"
#include "Games.h"
#include "Room.h"
#include <JobQueue.h>

shared_ptr<Games> Ggames = make_shared<Games>();

void Games::NewGame(vector<PlayerRef> players, int32 level, int32 room)
{
	_games[room] = RoomInfo(make_shared<Room>(level, room));

	_games[room]()->MatchEnter(std::move(players));
}

void Games::EnterGame(GameSessionRef session, int64 id, int32 room)
{
	//TODO 학인 절차
	
	//테스트 코드
	if (TEST)
	{
		if (!IsRoom(room)) 
		{
			_games[room] = RoomInfo(make_shared<Room>(2, room));
			session->_room = _games[room]();
			_games[room]()->GameEnter(session, id);
			_games[room] << id;

			DoTimer(5000, &Games::StartGame, room);
			auto _ref = GetNpcRef();
			if (_ref != nullptr) 
			{
				Npc::LoginData data;
				data.set_maplevel(2);
				data.set_matchroom(0);

				_ref->Send(NpcHandler::MakeSendBuffer(data, Npc::LOGIN));
			}
			else {
				Npc::LoginData input;
				input.set_maplevel(2);
				input.set_matchroom(0);
				auto ob = input.add_obstacle();
				ob->set_id(1);
				ob->set_shape(1);
				ob->set_speed(10.f);
				GameUtils::SetVector3(ob->mutable_position(), 1.f, 1.f, 1.f);
				GameUtils::SetVector3(ob->mutable_rotation(), 1.f, 1.f, 1.f);

				_games[room]()->ObstacleEnter(input);
			}
		}
		else {
			if (!_games[room])
			{
				if (_games[room] >> id)
				{
					session->_room = _games[room]();
					_games[room]()->DoAsync(&Room::ReConnect, session, id);
				}
			}
			else
			{
				if (_games[room]()->IsPlayer(id))
				{
					cout << "Player Inside = " << id << " " << room << endl;
					session->_room = _games[room]();
					_games[room]()->GameEnter(session, id);
					_games[room] << id;
				}
			}
		}
	}
	//고쳐보기 맘에 안듬
	else if (IsRoom(room)) 
	{
		if (!_games[room]) 
		{
			if (_games[room] >> id) 
			{
				_games[room]()->DoAsync(&Room::ReConnect, session, id);
			}
		}
		else 
		{
			if (_games[room]()->IsPlayer(id))
			{
				cout << "Player Inside = " << id << " " << room << endl;
				session->_room = _games[room]();
				_games[room]()->GameEnter(session, id);
				_games[room] << id;
			}
		}
	}
	// 재 접속 코드 넣기
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
	if ((check = _games[room]()->Start()) == -1) 
	{
		DoTimer(5000, &Games::StartGame, room);
		return;
	}
	else if(GetNpcRef() != nullptr)
	{
		Npc::StartData data;
		data.set_game(true);
		data.set_room(room);
		data.set_size(check);
		GetNpcRef()->Send(NpcHandler::MakeSendBuffer(data, Npc::START));
	}
	cout << "게임 시작" << endl;
	_games[room] == true;
	//게임 시작
}

void Games::EndGame(int32 room)
{
	_games.erase(room);
	
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
