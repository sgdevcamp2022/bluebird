#pragma once
#include "Room.h"

class Rooms : JobQueue
{
public:
	Rooms();
	~Rooms();

	void MakeRoom(vector<PlayerRef> players, Protocol::Data);

private:
	vector<Room> _rooms;
};

