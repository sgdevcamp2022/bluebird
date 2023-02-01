#pragma once
#include <hiredis/hiredis.h>
#include <string>
#include <cstring>

class Redis
{
public:
	Redis();
	~Redis();
	const char* RedisQuery(const char* format);
	const char* RedisQuery(const char* format, const char* arg1);
	const char* RedisQuery(const char* format, const char* arg1, const char* arg2);

private:
	redisContext* context;
	redisReply* reply;

	char* res = (char*)malloc(sizeof(char)*10);

	const char* host = "34.84.148.50";
	const char* password = "a12b34";
	int port = 6379;
};