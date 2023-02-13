#pragma once
#include "Room.h"

struct RoomInfo
{
public:
	RoomInfo() {}
	RoomInfo(RoomRef ref) : _room(ref) { }
	~RoomInfo() { _room = nullptr; }

	RoomRef operator()() { return _room; }

	bool operator>>(const int i) {
		if (find(_player.begin(), _player.end(), i) != _player.end())
			return true;
		return false;
	}
	void operator<<(const int i) {
		_player.push_back(i);
	}
	void operator==(bool start) {
		_start = start;
	}
	bool operator!() {
		return _start;
	}
private:
	RoomRef			_room;
	vector<int64>	_player;
	bool			_start = false;
};

class Games : public JobQueue
{
public:
	Games() { };
	~Games() { _games.clear(); };

	void			NewGame(vector<PlayerRef> players, int32 level, int32 room);
	void			EnterGame(GameSessionRef session, int64 id, int32 room);
	void			StartGame(int32 room);
	void			NextStageGame(int32 room, int32 level);
	void			EndGame(int32 room);

	bool			IsRoom(int64 id);
	RoomRef			GetRoomRef(int32 room) { return _games[room](); }
	void			SetNpcRef(NpcSessionRef);
	NpcSessionRef	GetNpcRef() { return _npcRef; }

private:
	map<int32, RoomInfo>		_games;
	NpcSessionRef				_npcRef = nullptr;
};

extern shared_ptr<Games> Ggames;

