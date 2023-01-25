#pragma once
class Creature
{
public:
	Creature(int64 id, int32 room, Vector3 position = Vector3{ 0,0,0 })
		:_id(id), _room(room), _position(position) {}

	Vector3&		GetPosition() { return _position; }
	int64			GetId() { return _id; }
	int32			GetRoom() { return _room; }
	virtual void	MovePosition(Vector3&& position) abstract = 0;
	

protected:
	int64			_id = 0;
	int32			_room = 0;
	Vector3			_position;
	
};

class Player : public Creature
{
public:
	Player(int64 id, int32 room, Vector3 position = Vector3{ 0,0,0 })
		: Creature(id, room, position) {}

	GameSessionRef	GetOwner() { return _ownerSession; }
	void			SetOwner(GameSessionRef session) { _ownerSession = session; }
	virtual void	MovePosition(Vector3&& position);

private:
	GameSessionRef	_ownerSession = nullptr;
};

class Obtacle : public Creature {
public:
	Obtacle(int64 id, int32 shape, int32 room, Vector3 position = Vector3{ 0,0,0 })
		: _shape(shape), Creature(id, room, position) {}

	virtual void	MovePosition(Vector3&& position);
	int32			GetShape() { return _shape; }

private:
	int32 _shape;
};
