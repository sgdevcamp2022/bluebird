#include "pch.h"
#include "MatchRoom.h"
#include "MatchSession.h"
#include "Player.h"

int MatchRoom::Enter(PlayerRef player)
{
	_players[player->playerId] = player;

	return _players.size();
}

void MatchRoom::Leave(PlayerRef player)
{
	_players.erase(player->playerId);
}

void MatchRoom::Broadcast(SendBufferRef sendBuffer)
{
	for (auto& p : _players)
	{
		p.second->ownerSession->Send(sendBuffer);
	}
}

