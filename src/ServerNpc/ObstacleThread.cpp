#include "ServerNpc.h"

ObstacleThread::ObstacleThread(LoginData loginData, int index, ServerNpc& npcServer) : loginData(loginData), npcServer(npcServer)
{
    gameData.matchRoom = loginData.matchRoom;
    gameData.obstacle = loginData.obstacle[index];
    roomGroup = npcServer.GetStartData();
}

void ObstacleThread::operator()()
{
    bool isStart = false;
    while (!isStart)
    {
        for (iterRoom = roomGroup->begin(); iterRoom != roomGroup->end(); iterRoom++)
        {
            if (iterRoom->room == loginData.matchRoom && iterRoom->game == true)
            {
                isStart = true;
                break;
            }
        }
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
    }

    switch (gameData.obstacle.obstacleShape)
    {
    case 0:
        MovingObstacle();
        break;

    case 1:
        MovingObstacle();
        break;

    case 2:
        RotationObstacle();
        break;

    default:
        break;
    }
}

void ObstacleThread::MovingObstacle()
{
    float startPosX = gameData.obstacle.positionX;
    float startPosY = gameData.obstacle.positionY;
    float startPosZ = gameData.obstacle.positionZ;
    bool goPositive = true;
    float deltaTime = gameData.obstacle.distance / gameData.obstacle.speed;
    boost::chrono::duration<float> waitTime(deltaTime);

    while (true)
    {
        switch (gameData.obstacle.direction)
        {
        case 0:
        {
            if (goPositive)
            {
                gameData.obstacle.positionX = startPosX;
                goPositive = !goPositive;
                npcServer.PostWrite(gameData);
            }
            else
            {
                gameData.obstacle.positionX += gameData.obstacle.distance;
                goPositive = !goPositive;
                npcServer.PostWrite(gameData);
            }
            break;
        }
        case 1:
        {
            if (goPositive)
            {
                gameData.obstacle.positionY = startPosY;
                goPositive = !goPositive;
                npcServer.PostWrite(gameData);
            }
            else
            {
                gameData.obstacle.positionY += gameData.obstacle.distance;
                goPositive = !goPositive;
                npcServer.PostWrite(gameData);
            }
            break;
        }
        case 2:
        {
            if (goPositive)
            {
                gameData.obstacle.positionZ = startPosZ;
                goPositive = !goPositive;
                npcServer.PostWrite(gameData);
            }
            else
            {
                gameData.obstacle.positionZ += gameData.obstacle.distance;
                goPositive = !goPositive;
                npcServer.PostWrite(gameData);
            }
            break;
        }
        default:
            break;
        }

        boost::this_thread::sleep_for(waitTime);
    }
}

void ObstacleThread::RotationObstacle()
{
    //float deltaTime = 360.0f / (gameData.obstacle.speed / 0.045);
    //boost::chrono::duration<float> waitTime(deltaTime);
    //while (true)
    //{
    //    gameData.obstacle.rotationZ = -180;
    //    cout << "MatchRoom: " << gameData.matchRoom << " | RotZ: " << gameData.obstacle.rotationZ << endl;
    //    npcServer.PostWrite(gameData);
    //    boost::this_thread::sleep_for(waitTime);
    //}
}
