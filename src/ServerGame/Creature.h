#pragma once
class Creature
{
public:
	Creature(int64 id, Vector3 position = Vector3{ 0,0,0 })
		:_id(id), _position(position) {}

	Vector3&		GetPosition() { return _position; }
	virtual void	MovePosition(Vector3 position) abstract = 0;
	int64			GetId() { return _id; }

protected:
	int64			_id = 0;
	Vector3			_position;
	
};

class Player : public Creature
{
public:
	Player(int64 id, Vector3 position = Vector3{ 0,0,0 })
		: Creature(id, position) {}

	GameSessionRef	GetOwner() { return _ownerSession; }
	void			SetOwner(GameSessionRef session) { _ownerSession = session; }
	virtual void	MovePosition(Vector3 position);

private:
	GameSessionRef	_ownerSession = nullptr;
};

class Obtacle : public Creature {
public:
	Obtacle(int64 id, int32 shape, Vector3 position = Vector3{ 0,0,0 })
		: _shape(shape), Creature(id, position) {}

	virtual void	MovePosition(Vector3 position);
	int32			GetShape() { return _shape; }

private:
	int32 _shape;
};
