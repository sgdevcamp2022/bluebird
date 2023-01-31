#pragma once
class GameObject
{
public:
	GameObject(int64 id, int32 room, Vector3 position)
		:_id(id), _room(room), _position(position) {}

	Vector3&		GetPosition() { return _position; }
	void			SetPosition(Vector3 position) { _position = position; }
	virtual void	MovePosition(Vector3&& position) abstract = 0;
	int64			GetId() { return _id; }
	int32			GetRoom() { return _room; }

protected:
	int64			_id = 0;
	int32			_room = 0;
	Vector3			_position;
	
};

class Player : public GameObject
{
public:
	Player(int64 id, int32 room, Vector3 position = Vector3{ 0,0,0 })
		: GameObject(id, room, position) {}

	GameSessionRef	GetOwner() { return _ownerSession; }
	void			SetOwner(GameSessionRef session) { _ownerSession = session; }
	virtual void	MovePosition(Vector3&& position);

private:
	GameSessionRef	_ownerSession = nullptr;
};

class Obtacle : public GameObject {
public:
	Obtacle(int64 id, int32 shape, int32 room, Vector3 position = Vector3{ 0,0,0 })
		: _shape(shape), GameObject(id, room, position) {}

	virtual void	MovePosition(Vector3&& position);
	int32			GetShape() { return _shape; }

private:
	int32 _shape;
};
