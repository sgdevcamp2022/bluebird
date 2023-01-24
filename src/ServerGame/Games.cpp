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

void Games::EndGame()
{
	//TODO
}

RoomRef Games::GetRoom(int32 id)
{
	//에러체크 TODO

	return _games[id];
}

void Games::SetNpcRef(NpcSessionRef ref)
{
	if (_npcRef == nullptr)
		_npcRef = ref;
}
