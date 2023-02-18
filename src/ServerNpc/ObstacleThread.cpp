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
    float distanceSum = 0;
    float startPosX = gameData.obstacle.positionX;
    float startPosY = gameData.obstacle.positionY;
    float startPosZ = gameData.obstacle.positionZ;
    bool goPositive = true;
    float deltaTime = 0.01667;

    while (true)
    {

        switch (gameData.obstacle.direction)
        {
        case 0: //XÃà
        {
            if (goPositive)
            {
                gameData.obstacle.positionX += gameData.obstacle.speed * deltaTime;
            }
            else
            {
                gameData.obstacle.positionX -= gameData.obstacle.speed * deltaTime;
            }
            distanceSum += gameData.obstacle.speed * deltaTime;

            if (distanceSum > gameData.obstacle.distance)
            {
                gameData.obstacle.positionX < startPosX ? gameData.obstacle.positionX = startPosX : gameData.obstacle.positionX = (startPosX + gameData.obstacle.distance);
                distanceSum = 0;
                goPositive = !goPositive;
                cout << "MatchRoom: " << gameData.matchRoom << " | ObsID: " << gameData.obstacle.obstacleID << " | posX: " << gameData.obstacle.positionX << " | posY: " << gameData.obstacle.positionY << " | posZ: " << gameData.obstacle.positionZ << endl;
                npcServer.PostWrite(gameData);
            }
            break;
        }
        case 1: //YÃà
        {
            if (goPositive)
            {
                gameData.obstacle.positionY += gameData.obstacle.speed * deltaTime;
            }
            else
            {
                gameData.obstacle.positionY -= gameData.obstacle.speed * deltaTime;
            }
            distanceSum += gameData.obstacle.speed * deltaTime;

            if (distanceSum > gameData.obstacle.distance)
            {
                gameData.obstacle.positionY < startPosY ? gameData.obstacle.positionY = startPosY : gameData.obstacle.positionY = (startPosY + gameData.obstacle.distance);
                distanceSum = 0;
                goPositive = !goPositive;
                cout << "MatchRoom: " << gameData.matchRoom << " | ObsID: " << gameData.obstacle.obstacleID << " | posX: " << gameData.obstacle.positionX << " | posY: " << gameData.obstacle.positionY << " | posZ: " << gameData.obstacle.positionZ << endl;
                npcServer.PostWrite(gameData);
            }
            break;
        }
        case 2: //ZÃà
        {
            if (goPositive)
            {
                gameData.obstacle.positionZ += gameData.obstacle.speed * deltaTime;
            }
            else
            {
                gameData.obstacle.positionZ -= gameData.obstacle.speed * deltaTime;
            }
            distanceSum += gameData.obstacle.speed * deltaTime;

            if (distanceSum > gameData.obstacle.distance)
            {
                gameData.obstacle.positionZ < startPosZ ? gameData.obstacle.positionZ = startPosZ : gameData.obstacle.positionZ = (startPosZ + gameData.obstacle.distance);
                distanceSum = 0;
                goPositive = !goPositive;
                cout << "MatchRoom: " << gameData.matchRoom << " | ObsID: " << gameData.obstacle.obstacleID << " | posX: " << gameData.obstacle.positionX << " | posY: " << gameData.obstacle.positionY << " | posZ: " << gameData.obstacle.positionZ << endl;
                npcServer.PostWrite(gameData);
            }
            break;
        }
        default:
            break;
        }
        boost::this_thread::sleep_for(boost::chrono::microseconds(16670));
    }
}

void ObstacleThread::RotationObstacle()
{
    float deltaTime = 0.01667;
    while (true)
    {
        gameData.obstacle.rotationZ += gameData.obstacle.speed * deltaTime / 0.05f;
        if (gameData.obstacle.rotationZ > 180)
        {
            gameData.obstacle.rotationZ = -180;
            cout << "MatchRoom: " << gameData.matchRoom << " | RotZ: " << gameData.obstacle.rotationZ << endl;
            npcServer.PostWrite(gameData);
        }
        boost::this_thread::sleep_for(boost::chrono::microseconds(16670));
    }
}
