#pragma once
class Player
{
public:
	int64	playerId	= 0;
	int32	mapLevel	= 0;
	MatchSessionRef ownerSession = nullptr;
};

