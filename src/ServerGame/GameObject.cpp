#include "pch.h"
#include "GameObject.h"

Player::~Player() {
	_ownerSession = nullptr;
	_ownerPlayer = nullptr;
	cout << _id << " Player 삭제" << endl;
}

bool Player::Move(Vector3&& position, Vector3&& rotation)
{
	if (_move) {
		GameUtils::SetVector3(_position, position);
		GameUtils::SetVector3(_rotation, rotation);
		return true;
	}
	return false;
}

void Player::SetPlayer(Protocol::Player* ref)
{
	_ownerPlayer = ref;
	_ownerPlayer->set_id(_id);

	_position = _ownerPlayer->mutable_position();
	_rotation = _ownerPlayer->mutable_rotation();
}

Obtacle::~Obtacle() {
	_ownerObtacle = nullptr;
	cout << _id << " Obstalce 삭제" << endl;
}

bool Obtacle::Move(Vector3&& position, Vector3&& rotation)
{
	GameUtils::SetVector3(_position, position);
	GameUtils::SetVector3(_rotation, rotation);

	return true;
}

GameObject::~GameObject()
{
	_position = nullptr;
	_rotation = nullptr;
}

void Obtacle::SetObstacle(Protocol::Obtacle* ref)
{
	_ownerObtacle = ref;
	ref->set_shape(_shape);
	ref->set_speed(_speed);
	_ownerObtacle->set_id(_id);
	
	_position = _ownerObtacle->mutable_position();
	_rotation = _ownerObtacle->mutable_rotation();
}