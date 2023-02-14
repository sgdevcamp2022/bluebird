#include "pch.h"
#include "Games.h"
#include "Room.h"
#include <JobQueue.h>

shared_ptr<Games> Ggames = make_shared<Games>();

void Games::NewGame(vector<PlayerRef> players, int32 level, int32 room)
{
	_games[room] = RoomInfo(make_shared<Room>(level, room));

	_games[room]()->MatchEnter(std::move(players));
	if(NPC_TEST)
		_games[room].SetNpc(true);
}

void Games::EnterGame(GameSessionRef session, int64 id, int32 room)
{
	//TODO 학인 절차
	
	//테스트 코드
	if (CLIENT_TEST)
	{
		if (!IsRoom(room)) 
		{
			cout << "Player Inside1 = " << id << " " << room << endl;
			_games[room] = RoomInfo(make_shared<Room>(2, room));
			session->_room = _games[room]();
			_games[room]()->GameEnter(session, id);
			_games[room] << id;

			DoTimer(3000, &Games::StartGame, room);
			auto _ref = GetNpcRef();
			if (_ref != nullptr) 
			{
				Npc::LoginData data;
				data.set_maplevel(1);
				data.set_matchroom(room);

				_ref->Send(NpcHandler::MakeSendBuffer(data, Npc::LOGIN));
			}
			else{
				if (NPC_TEST)
					_games[room].SetNpc(true);
				Npc::LoginData input;
				input.set_maplevel(1);
				input.set_matchroom(room);
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
			if (_games[room].CheckStart())
			{
				if (_games[room] >> id)
				{
					cout << "reconnect" << endl;
					session->_room = _games[room]();
					_games[room]()->DoAsync(&Room::ReConnect, session, id);
				}
			}
			else if(!(_games[room] >> id))
			{
				cout << "Player Inside2 = " << id << " " << room << endl;
				session->_room = _games[room]();
				_games[room]()->GameEnter(session, id);
				_games[room] << id;
			}
		}
	}
	//고쳐보기 맘에 안듬
	else if (IsRoom(room)) 
	{
		if (_games[room].CheckStart()) 
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
		Protocol::ConnectData data;
		data.set_id(id);
		data.set_room(-1);
		session->Send(GameHandler::MakeSendBuffer(data, Protocol::CONNECT_FAIL));
	}
}

void Games::EnterNpc(Npc::LoginData pkt, int32 room)
{
	_games[room]()->ObstacleEnter(std::move(pkt));
	_games[room].SetNpc(true);
}

void Games::StartGame(int32 room)
{
	int check = 0;
	if (_games[room].CheckNpc() && (check = _games[room]()->Start()))
	{
		cout << "게임 시작 " << room << endl;
		if (GetNpcRef() != nullptr)
		{
			Npc::StartData data;
			data.set_game(true);
			data.set_room(room);
			data.set_size(check);
			GetNpcRef()->Send(NpcHandler::MakeSendBuffer(data, Npc::START));
		}	
		_games[room].SetStart(true);
	}
	else
	{
		cout << check << endl;
		DoTimer(1000, &Games::StartGame, room);
		return;
	}
	//게임 시작
}

void Games::NextStageGame(int32 room, int32 level, int32 stage)
{
	if (_npcRef != nullptr) {
		_games[room].SetNpc(false);
		Npc::NextStage data;
		data.set_level(level);
		data.set_room(room);
		data.set_stage(stage);

		_npcRef->Send(NpcHandler::MakeSendBuffer(data, Npc::NEXT));
	}
	DoTimer(4000, &Games::StartGame, room);
}

void Games::EndGame(int32 room, int32 level)
{
	if (_npcRef != nullptr) {
		Npc::EndGame data;
		data.set_level(level);
		data.set_room(room);

		_npcRef->Send(NpcHandler::MakeSendBuffer(data, Npc::END));
	}

	//TODO

	_games.erase(room);
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
