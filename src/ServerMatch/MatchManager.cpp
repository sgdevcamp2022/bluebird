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
	//에러 체크 필요함
	int count = _matchRooms[roomNum]->Enter(player);
	if (count == ROOM_COUNT) {
		//브로드 캐스트 이후에 확인 작업 필요 한가..?
		_matchRooms[roomNum]->Broadcast(_ref);

		_matchRooms[roomNum]->Clear();
	}
	
}

void MatchManager::MatchLeave(PlayerRef player, int32 roomNum)
{
	_matchRooms[roomNum]->Leave(player);
}

void MatchManager::SetService(ClientServiceRef ref)
{
	_ref = ref;
}
