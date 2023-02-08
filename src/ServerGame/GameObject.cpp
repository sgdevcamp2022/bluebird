#include "pch.h"
#include "GameObject.h"

bool Player::Move(Vector3&& position, Vector3&& rotation)
{
	_position = position;
	_rotation = rotation;

	GameUtils::SetVector3(_ownerPlayer->mutable_position(), _position);
	GameUtils::SetVector3(_ownerPlayer->mutable_rotation(), _rotation);

	return true;
}

void Player::SetPlayer(Protocol::Player* ref)
{
	_ownerPlayer = ref;
	_ownerPlayer->set_id(_id);
	GameUtils::SetVector3(_ownerPlayer->mutable_position(), _position);
	GameUtils::SetVector3(_ownerPlayer->mutable_rotation(), _rotation);
}

bool Obtacle::Move(Vector3&& position, Vector3&& rotation)
{
	_position = position;
	_rotation = rotation;

	return true;
}

GameObject::~GameObject()
{
	cout << "Object »èÁ¦" << endl;
}

void Obtacle::SetObstacle(Protocol::Obtacle* ref)
{
	_ownerObtacle = ref;
	ref->set_shape(_shape);
	ref->set_speed(_speed);
	_ownerObtacle->set_id(_id);
	GameUtils::SetVector3(_ownerObtacle->mutable_position(), _position);
	GameUtils::SetVector3(_ownerObtacle->mutable_rotation(), _rotation);
}