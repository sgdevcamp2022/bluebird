#include "pch.h"
#include "GameObject.h"

bool Player::Move(Vector3&& position, Vector3&& rotation)
{
	_position = position;
	_rotation = rotation;

	return true;
}

bool Obtacle::Move(Vector3&& position, Vector3&& rotation)
{
	_position = position;
	_rotation = rotation;

	return true;
}
