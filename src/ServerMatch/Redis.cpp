#include "pch.h"
#include "Redis.h"
#include <iostream>

shared_ptr<Redis> GRedis = make_shared<Redis>();

Redis::Redis()
{
    context = redisConnect(host, port);
    if (context == NULL || context->err)
    {
        cout << "Redis Connection Error" << endl;
        return;
    }

    reply = (redisReply*)redisCommand(context, "AUTH %s", password);
    freeReplyObject(reply);
}

Redis::~Redis()
{
    free(res);
    redisFree(context);
}

const char* Redis::RedisQuery(const char* format)
{
    reply = (redisReply*)redisCommand(context, format);
    strcpy_s(res, strlen(reply->str)+1, reply->str);
    freeReplyObject(reply);
    return res;
}

const char* Redis::RedisQuery(const char* format, const char* arg1)
{
    reply = (redisReply*)redisCommand(context, format, arg1);
    strcpy_s(res, strlen(reply->str)+1, reply->str);
    freeReplyObject(reply);
    return res;
}

const char* Redis::RedisQuery(const char* format, const char* arg1, const char* arg2)
{
    reply = (redisReply*)redisCommand(context, format, arg1, arg2);
    strcpy_s(res, strlen(reply->str)+1, reply->str);
    freeReplyObject(reply);
    return res;
}

bool Redis::ExistQuery(int userNo)
{
    string tempStr = "exists ";
    bool res = 0;
    tempStr += to_string(userNo);
    reply = (redisReply*)redisCommand(context, tempStr.c_str());
    res = reply->integer;
    freeReplyObject(reply);
    return res;
}
