#include "pch.h"
#include "MatchManager.h"
#include "MatchSession.h"
#include "ConnectSession.h"
#include "RedisManager.h"
#include "Redis.h"

shared_ptr<MatchManager> GMatch = make_shared<MatchManager>();

MatchManager::MatchManager()
{
	_playerSize[SOLO] = 0;
	_playerSize[DUO] = 0;
	_playerSize[THREE] = 0;
}

MatchManager::~MatchManager()
{
	
}

void MatchManager::MatchEnter(int64 id, int32 level)
{
	Redis* redis = GRedisManager->GetRedis();
	if (redis == nullptr) {
		cout << "nullptr" << endl;
		DoAsync(&MatchManager::MatchEnter, id, level);
		return;
	}

	if (redis->ExistQuery(id)) {
		cout << "Login : " << id << " " << level << endl;
		Match::S_Login data;
		data.set_id(id);
		data.set_level(level);
		if (_lobyref != nullptr)
			_lobyref->Send(PacketHandler::MakeSendBuffer(data, Match::S_LOGIN));

		int32 type = 0;
		if (level & SOLO)
		{
			type |= PlayerInsideMatch(SOLO, id);
			DoTimer(1000, &MatchManager::PlayerOutputMatch, { SOLO, SOLO_DUO, SOLO_THREE }, SOLO_PLAYER_COUNT, SOLO_MAX_PLAYER_COUNT);
		}
		if (level & DUO)
		{
			type |= PlayerInsideMatch(DUO, id);
			DoTimer(1000, &MatchManager::PlayerOutputMatch, { DUO, SOLO_DUO, DUO_THREE }, DUO_PLAYER_COUNT, DUO_MAX_PLAYER_COUNT);
		}
		if (level & THREE)
		{
			type |= PlayerInsideMatch(THREE, id);
			DoTimer(1000, &MatchManager::PlayerOutputMatch, { THREE, SOLO_THREE, DUO_THREE }, THREE_PLAYER_COUNT, THREE_MAX_PLAYER_COUNT);
		}
	}
	else {
		cout << "Redis에 없음 " << id << endl;
		Match::S_Login data;
		data.set_id(id);
		data.set_level(level);
		if (_lobyref != nullptr)
			_lobyref->Send(PacketHandler::MakeSendBuffer(data, Match::S_CANCLE));
	}
	GRedisManager->ReturnRedis(redis);
}

void MatchManager::MatchLeave(int64 id, int32 level, int32 room)
{
	//확인작업 필요
	auto f = find(_playerWait[level].begin(), _playerWait[level].end(), id);
	if (f != _playerWait[level].end())
	{
		_playerWait[level].erase(f);
	}
	{
		Match::S_Cancel data;
		data.set_id(id);
		data.set_room(level);
		data.set_state(true);
		if (_lobyref != nullptr)
			_lobyref->Send(PacketHandler::MakeSendBuffer(data, Match::S_CANCLE));
	}
	// 맞습니다...

	if (level & SOLO)
		_playerSize[SOLO].fetch_sub(1);
	if (level & DUO)
		_playerSize[DUO].fetch_sub(1);
	if (level & THREE)
		_playerSize[THREE].fetch_sub(1);
}

int32 MatchManager::PlayerInsideMatch(PlayerLevel level, int32 id)
{
	_playerWait[level].push_back(id);
	_playerSize[level].fetch_add(1);
	if (_playerSize[level] >= SOLO_PLAYER_COUNT)
		return level;
	else
		return EMPTY;
}

void MatchManager::PlayerOutputMatch(array<PlayerLevel, 3> levels, int32 min, int32 max)
{
	Match::S_Match _users;

	if (_playerSize[levels[0]] >= min) {
		for (int level : levels) {
			while (!_playerWait[level].empty()) {
				if (_users.ids_size() == max)
					break;
				_users.add_ids(_playerWait[level].front());
				_playerWait[level].pop_front();
			}
		}
		_playerSize[levels[0]] -= _users.ids_size();
		cout << "OutSize : " << _users.ids_size() << endl;

		_users.set_room(_roomId.fetch_add(1));
		_users.set_level(levels[0]);

		if (_gameref != nullptr) {
			_gameref->Send(PacketHandler::MakeSuccessBuffer(_users, Match::S_MATCH));
			cout << "GameRef Send" << endl;
		}
		if (_matchref != nullptr) {
			_matchref->Send(PacketHandler::MakeSendBuffer(_users, Match::S_MATCH));
			cout << "MatchRef Send" << endl;
		}
	}
}

void MatchManager::ConnectGameServer(ConnectSessionRef ref)
{
	_gameref = ref;
}

void MatchManager::ConnectMatchServer(MatchSessionRef ref)
{
	cout << "Connect Match" << endl;
	_matchref = ref;
}

void MatchManager::ConnectLobyServer(MatchSessionRef ref)
{
	cout << "Connect Loby" << endl;
	_lobyref = ref;
}