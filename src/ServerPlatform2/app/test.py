import aioredis

import asyncio

async def main():
    redis = aioredis.from_url("redis://:a12b34@34.84.148.50:6379")
    id = 1
    await redis.hset(1,"height",180)
    await redis.hset(1,"emotion","happy")
    await redis.hset(2,"emotion","sad")
    print()
    print("Key 1에 height 180 등록")
    print("Key 1에 emotion 'happy' 등록")
    print("Key 2에 emotion 'sad' 등록")
    print()
    value1 = await redis.hget(1,"height")
    value2 = await redis.hgetall(1)
    value3 = await redis.hget(2,"emotion")
    print(value1, "=> hget(1, 'height') # Key 1의 height 값")
    print(value2, "=> hgetall(1) # Key 1의 field와 value 전부 가져오기")
    print(value3, "=> hget(2, 'emotion') # Key 2의 emotion 값")
    await redis.delete(1)
    print()
    print("Key 1 캐시 삭제 후")
    print()
    value4 = await redis.hget(1,"height")
    value5 = await redis.hget(2,"emotion")
    print(value4, "=> hget(1, 'height') # Key 1의 height 값")
    print(value5, "=> hget(2, 'emotion') # Key 2의 emotion 값")
    print()
    print("redis에 저장된 캐시 전부 삭제 후")
    print()
    await redis.flushall()
    value6 = await redis.hget(1,"emotion")
    value7 = await redis.hget(2,"emotion")
    print(value6, "=> hget(1, 'emotion') # Key 1의 emotion 값")
    print(value7, "=> hget(2, 'emotion') # Key 2의 emotion 값")

if __name__ == "__main__":
    asyncio.set_event_loop_policy(asyncio.WindowsSelectorEventLoopPolicy())
    asyncio.run(main())
