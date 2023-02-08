#pragma once
class GameObject
{
public:
	GameObject(int64 id, int32 room, Vector3 position, Vector3 rotation, float speed)
		:_id(id), _room(room), _position(position), _rotation(rotation), _speed(speed) {}
	virtual ~GameObject();

	Vector3&		GetPosition() { return _position; }
	void			SetPosition(Vector3 position) { _position = position; }
	Vector3&		GetRotation() { return _rotation; }
	void			SetRotation(Vector3 rotation) { _rotation = rotation; }
	virtual bool	Move(Vector3&& position, Vector3&& rotation) abstract = 0;
	float			GetSpeed() { return _speed; }
	int64			GetId() { return _id; }
	int32			GetRoom() { return _room; }

protected:
	int64			_id = 0;
	int32			_room = 0;
	float			_speed;
	Vector3			_position;
	Vector3			_rotation;
};

class Player : public GameObject
{
public:
	Player(int64 id, int32 room, Vector3 position = Vector3{ 0,0,0 }, Vector3 rotation = Vector3{ 0,0,0 }, float speed = 10.0f)
		: GameObject(id, room, position, rotation, speed) {}

	void			SetPlayer(Protocol::Player* ref);
	virtual bool	Move(Vector3&& position, Vector3&& rotation);

	GameSessionRef	GetOwner() { return _ownerSession; }
	void			SetOwner(GameSessionRef session) { _ownerSession = session; }

private:
	GameSessionRef		_ownerSession = nullptr;
	Protocol::Player*	_ownerPlayer = nullptr;
};

class Obtacle : public GameObject {
public:
	Obtacle(int64 id, int32 shape, int32 room, Vector3 position = Vector3{ 0,0,0 }, Vector3 rotation = Vector3{ 0,0,0 }, float speed = 10.0f, int32 direction = 0)
		: _shape(shape), _direction(direction), GameObject(id, room, position, rotation, speed) {}

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
