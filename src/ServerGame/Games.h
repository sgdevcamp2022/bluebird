#pragma once
#include "Room.h"

class Games : public JobQueue
{
public:
	Games() { };
	~Games() { _games.clear(); };

	void			NewGame(vector<PlayerRef>* players, int32 level, int32 room);
	void			EnterGame(GameSessionRef session, int64 id, int32 room);
	void			StartGame(int32 room);
	void			EndGame();

	bool			IsRoom(int64 id);
	RoomRef			GetRoomRef(int32 room) { return _games[room]; }
	void			SetNpcRef(NpcSessionRef);
	NpcSessionRef	GetNpcRef() { return _npcRef; }

private:
	map<int32, RoomRef> _games;
	NpcSessionRef		_npcRef = nullptr;
};

extern shared_ptr<Games> Ggames;

