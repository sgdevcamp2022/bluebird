#pragma once
#include "Room.h"

class Games : public JobQueue
{
public:
	Games() { };
	~Games() { _games.clear(); };

	void			NewGame(vector<PlayerRef>* players, int32 level, int32 room);
	void			EndGame();
	//void			LeaveGame(PlayerRef);
	RoomRef			GetRoom(int32 id);
	void			SetNpcRef(NpcSessionRef);
	NpcSessionRef	GetNpcRef() { return _npcRef; }

private:
	map<int32, RoomRef> _games;
	NpcSessionRef		_npcRef = nullptr;
};

extern shared_ptr<Games> Ggames;

