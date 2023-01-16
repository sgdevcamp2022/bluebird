#pragma once
class Player
{
public:
	uint64	playerId	= 0;
	uint32	mapLevel	= 0;
	MatchSessionRef ownerSession = nullptr;
};

