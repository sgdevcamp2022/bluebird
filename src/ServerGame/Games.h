#pragma once
#include "Room.h"

class Games : JobQueue
{
public:
	Games();
	~Games();

	void StartGame(vector<PlayerRef> players, Protocol::Data);
	void EndGame(Protocol::Data);

private:
	vector<Room> games;
};

