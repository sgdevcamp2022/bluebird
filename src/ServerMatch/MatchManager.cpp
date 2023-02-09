#include "pch.h"
#include "MatchManager.h"
#include "MatchRoom.h"
#include "Player.h"
#include "MatchSession.h"
#include "ConnectSession.h"

shared_ptr<MatchManager> GMatch = make_shared<MatchManager>();

MatchManager::MatchManager()
{
	for (int i = 0; i < TestLevel; i++) {
		_matchRooms.push_back(vector<MatchRoomRef>());
		for (int j = 0; j < TestRoom; j++) {
			_matchRooms[i].push_back(make_shared<MatchRoom>());
		}
		_matchNums.push_back(0);
	}
}

MatchManager::~MatchManager()
{
	_matchRooms.();
}

void MatchManager::MatchEnter(MatchSessionRef session, PlayerRef player, int32 level)
{
	//에러 체크 필요함
	

	Match::S_Login data;
	data.set_id(player->playerId);
	data.set_level(player->mapLevel);
	data.set_room(room);
	
	session->Send(PacketHandler::MakeSendBuffer(data, Match::S_LOGIN));

	if (count == PLATER_COUNT) {
		cout << "Start" << endl;
		DoTimer(3000, &MatchManager::MatchPull, level, _roomId.fetch_add(1), room);
	}
	else if (count == MAX_PLAYER_COUNT) {
		_matchRooms[level].push_back(make_shared<MatchRoom>());
		_matchNums[level] = (_matchNums[level] + 1) % 10;
	}
}

void MatchManager::MatchLeave(int64 id, int32 level, int32 room)
{
	//확인작업 필요
	_matchRooms[level][room]->Leave(id);
}

void MatchManager::MatchPull(int32 level, int32 match, int32 room)
{
	//브로드 캐스트 이후에 확인 작업 필요 한가..?
	_matchRooms[level][room]->Broadcast(_users, match);

	_users.set_room(match);
	_users.set_level(level);

	if(_gameref != nullptr)
		_gameref->Send(PacketHandler::MakeSuccessBuffer(_users, Match::S_MATCH));
	if(_lobyref != nullptr)
		_lobyref->Send(PacketHandler::MakeSendBuffer(_users, Match::S_MATCH));

	_users.Clear();

	//완료된 방 클리어
	_matchRooms[level][room]->Clear();

	if (room == _matchNums[level])
		_matchNums[level] = (_matchNums[level] + 1) % 10;
}

void MatchManager::ConnectGameServer(ConnectSessionRef ref)
{
	_gameref = ref;
}

void MatchManager::ConnectLobyServer(MatchSessionRef ref)
{
	_lobyref = ref;
}