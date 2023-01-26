#include "pch.h"
#include "Games.h"
#include "Room.h"
#include <JobQueue.h>

shared_ptr<Games> Ggames = make_shared<Games>();

void Games::NewGame(vector<PlayerRef>* players, int32 level, int32 room)
{
	_games[room] = make_shared<Room>(level, room);
	_games[room]->MatchEnter(players);
}

void Games::EnterGame(GameSessionRef session, int64 id, int32 room)
{
	if (IsRoom(room)) {
		session->_room = _games[room];
		_games[room]->GameEnter(session, id);
	}
}

void Games::StartGame(int32 room)
{
	_games[room]->Start();
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
