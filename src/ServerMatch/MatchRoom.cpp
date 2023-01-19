#include "pch.h"
#include "MatchRoom.h"
#include "MatchSession.h"
#include "Player.h"

int32 MatchRoom::Enter(PlayerRef player)
{
	_players[player->playerId] = player;

	return static_cast<int32>(_players.size());
}

void MatchRoom::Leave(PlayerRef player)
{
	_players.erase(player->playerId);
}

void MatchRoom::Broadcast(Match::Users& users, int32 matchRoom)
{
	users.set_usersize(static_cast<uint32>(_players.size()));

	for (auto& p : _players)
	{
		users.add_ids(p.second->playerId);
		Match::Success data;
		data.set_id(p.second->playerId);
		data.set_matchroom(matchRoom);
		data.set_gameport(5000);

		auto ref = PacketHandler::MakeSendBuffer(data, Match::S_MATCH);
		p.second->ownerSession->Send(ref);
	}
}

