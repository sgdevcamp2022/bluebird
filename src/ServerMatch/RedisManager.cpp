#include "pch.h"
#include "RedisManager.h"
#include "Redis.h"

RedisManager* GRedisManager = new RedisManager();

RedisManager::RedisManager()
{
	for (int i = 0; i < 10; i++) {
		Redis* tmp = new Redis;
		_redis.push(tmp);
		_tmp.push(tmp);
	}
}

RedisManager::~RedisManager()
{
	while(!_tmp.empty()) {
		delete _tmp.front();
		_tmp.pop();
	}
}

Redis* RedisManager::GetRedis()
{
	WRITE_LOCK;

	Redis* tmp = nullptr;
	
	if (!_redis.empty())
	{
		tmp = _redis.front();
		_redis.pop();
	}

	return tmp;
}

void RedisManager::ReturnRedis(Redis* redis)
{
	WRITE_LOCK;

	_redis.push(redis);
}