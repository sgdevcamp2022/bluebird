#include "pch.h"
#include "Players.h"

shared_ptr<Players> GPlayers = make_shared<Players>();

void Players::Enter(vector<PlayerRef>* ref)
{
	for(auto _ref : *ref)
		_players[_ref->_id] = _ref;
}

void Players::Leave(PlayerRef ref)
{
	_players.erase(ref->_id);
}
