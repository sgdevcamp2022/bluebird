#include "pch.h"
#include "GameObject.h"

void Player::MovePosition(Vector3&& position)
{
	_position.x = position.x;
	_position.y = position.y;
	_position.z = position.z;
}

void Obtacle::MovePosition(Vector3&& position)
{
	_position.x = position.x;
	_position.y = position.y;
	_position.z = position.z;
}
