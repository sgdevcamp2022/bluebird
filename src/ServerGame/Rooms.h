#pragma once
#include "Room.h"

class Rooms
{
public:
	Rooms();
	~Rooms();

	void MakeRoom(vector<PlayerRef> players);

private:
	vector<Room> _rooms;
};

