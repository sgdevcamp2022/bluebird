#include "pch.h"
#include "MatchManager.h"
#include "MatchRoom.h"
#include "Player.h"
shared_ptr<MatchManager> GMatch = make_shared<MatchManager>();

MatchManager::MatchManager()
{
	for (int i = 0; i < 5; i++) {
		_matchRooms.push_back(make_shared<MatchRoom>());
	}
}

MatchManager::~MatchManager()
{
	_matchRooms.clear();
}

void MatchManager::MatchEnter(PlayerRef player, int32 roomNum)
{
	if (roomNum > 5)
		return;
	int count = _matchRooms[roomNum]->Enter(player);
	cout << "Enter" << endl;
	if (count == ROOM_COUNT) {
		cout << "²ËÂü" << endl;
		Protocol::DATA data;

		data.set_id(player->playerId);
		data.set_maplevel(roomNum);
		data.set_state(true);

		auto ref = PacketHandler::MakeSendBuffer(data, Protocol::S_MATCH);
		_matchRooms[roomNum]->Broadcast(ref);

		_matchRooms[roomNum]->Clear();
	}
	
}

void MatchManager::MatchLeave(PlayerRef player, int32 roomNum)
{
	cout << "Leave" << endl;
	_matchRooms[roomNum]->Leave(player);
}