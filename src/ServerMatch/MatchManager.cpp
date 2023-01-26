#include "pch.h"
#include "MatchManager.h"
#include "MatchRoom.h"
#include "Player.h"
#include "MatchSession.h"

shared_ptr<MatchManager> GMatch = make_shared<MatchManager>();

MatchManager::MatchManager()
{
	for (int i = 0; i < 5; i++) {
		_matchRooms.push_back(vector<MatchRoomRef>());
		_matchNums.push_back(0);
	}
}

MatchManager::~MatchManager()
{
	_matchRooms.clear();
}

void MatchManager::MatchEnter(MatchSessionRef session, Match::Data data, PlayerRef player, int32 level)
{
	//에러 체크 필요함
	int32 match = _matchNums[level];
	int32 room = _matchRooms[level].size()-1;

	if (room == -1) {
		_matchRooms[level].push_back(make_shared<MatchRoom>());
		room += 1;
	}
	int32 count = _matchRooms[level][room]->Enter(player);

	data.set_state(true);
	data.set_room(room);
	
	session->Send(PacketHandler::MakeSendBuffer(data, Match::S_LOGIN));

	if (count == ROOM_COUNT) {
		DoTimer(3000, &MatchManager::MatchPull, level, match);
	}
	else if (count == MAX_ROOM_COUNT) {
		_matchRooms[level].push_back(make_shared<MatchRoom>());
		_matchNums[level]++;
	}
}

void MatchManager::MatchLeave(int64 id, int32 level, int32 room)
{
	//확인작업 필요
	if (level >= 5 && level < 0 && _matchRooms[level].size() < room)
		return;
	_matchRooms[level][room]->Leave(id);
}

void MatchManager::MatchPull(int32 level, int32 match)
{
	//브로드 캐스트 이후에 확인 작업 필요 한가..?
	_matchRooms[level][match]->Broadcast(_users, match);
	_users.set_room(match);
	_users.set_level(level);

	_ref->Broadcast(PacketHandler::MakeSendBuffer(_users, Match::S_MATCH));

	_users.Clear();

	//완료된 방 삭제
	_matchRooms[level].erase(_matchRooms[level].begin());
	if (match == _matchNums[level])
		_matchNums[level]++;
}

void MatchManager::SetService(ClientServiceRef ref)
{
	_ref = ref;
}
