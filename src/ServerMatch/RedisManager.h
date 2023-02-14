#pragma once

class Redis;

class RedisManager
{
public:
	RedisManager();
	~RedisManager();

	Redis*	GetRedis();
	void	ReturnRedis(Redis* redis);

private:
	USE_LOCK;
	queue<Redis*>	_redis;
	queue<Redis*>	_tmp;
};

extern RedisManager* GRedisManager;