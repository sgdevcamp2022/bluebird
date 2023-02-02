#include "ServerNpc.h"

ObstacleThread::ObstacleThread(LoginData loginData, ServerNpc& npcServer) : loginData(loginData), npcServer(npcServer)
{
    gameData.matchRoom = loginData.matchRoom;
    gameData.obstacleSize = loginData.obstacle.size();
    gameData.obstacle = loginData.obstacle;
}

void ObstacleThread::operator()() const
{
    while (true)
    {
        cout << "MatchRoom: " << gameData.matchRoom << endl;
        for (int i = 0; i < gameData.obstacleSize; i++)
        {
            cout << "Object ID: " << gameData.obstacle[i].obstacleID << " | Object Speed: " << gameData.obstacle[i].speed << endl;
            cout << "posX: " << gameData.obstacle[i].positionX << " | posY: " << gameData.obstacle[i].positionY << " | posZ: " << gameData.obstacle[i].positionZ << endl;
            cout << "posX: " << gameData.obstacle[i].rotationX << " | posY: " << gameData.obstacle[i].rotationY << " | posZ: " << gameData.obstacle[i].rotationZ << endl;
        }

        npcServer.PostWrite(gameData);
        boost::this_thread::sleep(boost::posix_time::seconds(1));
    }
}

void ObstacleThread::MovingObstacle()
{
    time_point<steady_clock> fpsTimer(steady_clock::now());
    frame FPS{};

    float maxX = 5.0f;
    float minX = 0.0f;

    bool goPositive = true;

    while (true)
    {
        FPS = duration_cast<frame>(steady_clock::now() - fpsTimer);
        if (FPS.count() >= 1)
        {
            fpsTimer = steady_clock::now();

            if (goPositive)
            {
                gameData.obstacle[0].positionX += gameData.obstacle[0].speed * duration_cast<sec>(FPS).count();
            }
            else
            {
                gameData.obstacle[0].positionX -= gameData.obstacle[0].speed * duration_cast<sec>(FPS).count();
            }
            
            if (gameData.obstacle[0].positionX > maxX || gameData.obstacle[0].positionX < minX)
            {
                goPositive = !goPositive;
                npcServer.PostWrite(gameData);
            }
        }
    }
}

void ObstacleThread::RotationObstacle()
{
}
