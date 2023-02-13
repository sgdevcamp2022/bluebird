#include "pch.h"
#include "MatchManager.h"
#include "MatchSession.h"
#include "ConnectSession.h"

shared_ptr<MatchManager> GMatch = make_shared<MatchManager>();

MatchManager::MatchManager()
{
	_playerSize[SOLO] = 0;
	_playerSize[DUO] = 0;
	_playerSize[THREE] = 0;

	_playerCount[SOLO] = [=](int32 id) {
		_playerWait[SOLO].push_back(id);
		_playerSize[SOLO] += 1;
		if (_playerSize[SOLO] >= SOLO_PLAYER_COUNT)
			return SOLO;
		else
			return EMPTY;
	};
	_playerCount[DUO] = [=](int32 id) {
		_playerWait[DUO].push_back(id);
		_playerSize[DUO] += 1;
		if (_playerSize[DUO] >= SOLO_PLAYER_COUNT)
			return DUO;
		else
			return EMPTY;
	};
	_playerCount[THREE] = [=](int32 id) {
		_playerWait[THREE].push_back(id);
		_playerSize[THREE] += 1;
		if (_playerSize[THREE] >= SOLO_PLAYER_COUNT)
			return THREE;
		else
			return EMPTY;
	};
	_playerCount[SOLO_DUO] = [=](int32 id) {
		if (_playerCount[DUO](id))
			return DUO;
		else if (_playerCount[SOLO](id))
			return SOLO;
		else
			return EMPTY;
	};
	_playerCount[SOLO_THREE] = [=](int32 id) {
		if (_playerCount[THREE](id))
			return THREE;
		else if (_playerCount[SOLO](id))
			return SOLO;	
		else
			return EMPTY;
	};
	_playerCount[DUO_THREE] = [=](int32 id) {
		if (_playerCount[DUO])
			return DUO;
		else if (_playerCount[THREE])
			return THREE;
		else
			return EMPTY;
	};
	_playerCount[ALL] = [=](int32 id) {
		if (_playerCount[SOLO](id))
			return SOLO;
		else if (_playerCount[DUO])
			return DUO;
		else if (_playerCount[THREE])
			return THREE;
		else
			return EMPTY;
	};

	// 디자인 패턴

	_playerOut = [=](Match::S_Match&  _users, array<PlayerLevel, 3> levels, int32 min, int32 max) {
		if (_playerSize[levels[0]] >= min) {
			for (int i = 0; i < levels.size(); i++) {
				while (!_playerWait[levels[i]].empty()) {
					if (_users.ids_size() == max)
						break;
					_users.add_ids(_playerWait[levels[i]].front());
					_playerWait[levels[i]].pop_front();
				}
			}
			_playerSize[levels[0]] -= _users.ids_size();
			cout << "OutSize : " << _users.ids_size() << endl;
		}
	};
}

MatchManager::~MatchManager()
{
	
}

void MatchManager::MatchEnter(int64 id, int32 level)
{
	//에러 체크 필요함

	Match::S_Login data;
	data.set_id(id);
	data.set_level(level);
	if (_lobyref != nullptr)
		_lobyref->Send(PacketHandler::MakeSendBuffer(data, Match::S_LOGIN));

	auto type = _playerCount[level](id);
	if (type)
		DoTimer(1000, &MatchManager::MatchPull, type);
}

void MatchManager::MatchLeave(int64 id, int32 level, int32 room)
{
	//확인작업 필요
	auto f = find(_playerWait[level].begin(), _playerWait[level].end(), id);
	if (f != _playerWait[level].end())
	{
		_playerWait[level].erase(f);
	}

	// 맞습니다...

	switch (level) {
	case SOLO:
		_playerSize[SOLO] -= 1;
		break;
	case DUO:
		_playerSize[DUO] -= 1;
		break;
	case THREE:
		_playerSize[THREE] -= 1;
		break;
	case SOLO_DUO:
		_playerSize[SOLO] -= 1;
		_playerSize[DUO] -= 1;
		break;
	case SOLO_THREE:
		_playerSize[SOLO] -= 1;
		_playerSize[THREE] -= 1;
		break;
	case DUO_THREE:
		_playerSize[DUO] -= 1;
		_playerSize[THREE] -= 1;
		break;
	case ALL:
		_playerSize[SOLO] -= 1;
		_playerSize[DUO] -= 1;
		_playerSize[THREE] -= 1;
		break;
	}
}

void MatchManager::MatchPull(int32 level)
{
	//브로드 캐스트 이후에 확인 작업 필요 한가..?	
	Match::S_Match _users;

	if (level == SOLO)
		_playerOut(_users, { SOLO, SOLO_DUO, SOLO_THREE }, SOLO_PLAYER_COUNT, SOLO_MAX_PLAYER_COUNT);
	else if (level == DUO)
		_playerOut(_users, { DUO, SOLO_DUO, DUO_THREE }, DUO_PLAYER_COUNT, DUO_MAX_PLAYER_COUNT);
	else if (level == THREE)
		_playerOut(_users, { THREE, SOLO_THREE, DUO_THREE }, THREE_PLAYER_COUNT, THREE_MAX_PLAYER_COUNT);

	if (_users.ids_size() == 0)
		return;

	_users.set_room(_roomId.fetch_add(1));
	_users.set_level(level);

	if (_gameref != nullptr) {
		_gameref->Send(PacketHandler::MakeSuccessBuffer(_users, Match::S_MATCH));
		cout << "GameRef Send" << endl;
	}
	if (_matchref != nullptr) {
		_matchref->Send(PacketHandler::MakeSendBuffer(_users, Match::S_MATCH));
		cout << "MatchRef Send" << endl;
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