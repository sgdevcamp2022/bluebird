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

void MatchRoom::Broadcast(ClientServiceRef& service)
{
	Match::Users datas;
	datas.set_usersize(_players.size());
	for (auto& p : _players)
	{
		auto data = datas.add_users();

		data->set_id(p.second->playerId);
		data->set_maplevel(p.second->mapLevel);
		data->set_state(true);

		auto ref = PacketHandler::MakeSendBuffer(*data, Match::S_MATCH);
		p.second->ownerSession->Send(ref);
	}
	auto ref = PacketHandler::MakeSendBuffer(datas, Match::S_MATCH);
	service->Broadcast(ref);
	cout << "Send" << endl;
}

