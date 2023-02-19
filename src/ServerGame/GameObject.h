#pragma once
#include "GameUtils.h"

class GameObject
{
public:
	GameObject(int64 id, int32 room, float speed)
		:_id(id), _room(room), _speed(speed) {}
	virtual ~GameObject();

	Protocol::Vector*	GetPosition() { return _position; }
	Protocol::Vector*	GetRotation() { return _rotation; }
	virtual bool		Move(Vector3&& position, Vector3&& rotation) abstract = 0;
	float				GetSpeed() { return _speed; }
	int64				GetId() { return _id; }
	int32				GetRoom() { return _room; }
	void				SetSpawnPoint(Npc::Vector3 position, Npc::Vector3 rotation) {
		GameUtils::SetVector3(_position, position);
		GameUtils::SetVector3(_rotation, rotation);
	}
protected:
	int64				_id = 0;
	int32				_room = 0;
	float				_speed;
	
	Protocol::Vector*	_position = nullptr;
	Protocol::Vector*	_rotation = nullptr;
};

class Player : public GameObject
{
public:
	Player(int64 id, int32 room, float speed = 10.0f)
		: GameObject(id, room, speed) {}
	virtual ~Player();

	void				SetPlayer(Protocol::Player* ref);
	virtual bool		Move(Vector3&& position, Vector3&& rotation);

	GameSessionRef		GetOwner() { return _ownerSession; }
	void				SetOwner(GameSessionRef session) { _ownerSession = session; }

	void				MoveChange() { _move = !_move; }
	bool				GetMoveRight() { return _move; }

private:
	bool					_move = true;
	GameSessionRef			_ownerSession = nullptr;
	Protocol::Player*		_ownerPlayer = nullptr;
};

class Obtacle : public GameObject {
public:
	Obtacle(int64 id, int32 shape, int32 room, float speed = 10.0f, int32 direction = 0)
		: _shape(shape), _direction(direction), GameObject(id, room, speed) {}
	virtual ~Obtacle();

	virtual bool	Move(Vector3&& position, Vector3&& rotation);
	void			SetObstacle(Protocol::Obtacle* ref);

	void			SetShape(int32 shape) { _shape = shape; }
	int32			GetShape() { return _shape; }
	int32			GetDirection() { return _direction; }
private:
	int32 _shape;
	int32 _direction;
	Protocol::Obtacle*	_ownerObtacle = nullptr;
};
