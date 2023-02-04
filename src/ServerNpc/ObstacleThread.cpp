#include "ServerNpc.h"

ObstacleThread::ObstacleThread(LoginData loginData,int index, ServerNpc& npcServer) : loginData(loginData), npcServer(npcServer)
{
    gameData.matchRoom = loginData.matchRoom;
    gameData.obstacle = loginData.obstacle[index];
}

void ObstacleThread::operator()()
{
    //while (true)
    //{
    //    cout << "MatchRoom: " << gameData.matchRoom << endl;
    //    cout << "Object ID: " << gameData.obstacle.obstacleID << " | Object Speed: " << gameData.obstacle.speed << endl;
    //    cout << "posX: " << gameData.obstacle.positionX << " | posY: " << gameData.obstacle.positionY << " | posZ: " << gameData.obstacle.positionZ << endl;
    //    cout << "posX: " << gameData.obstacle.rotationX << " | posY: " << gameData.obstacle.rotationY << " | posZ: " << gameData.obstacle.rotationZ << endl;
    //
    //    npcServer.PostWrite(gameData);
    //    boost::this_thread::sleep(boost::posix_time::seconds(1));
    //}
    MovingObstacle();
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
        if (FPS.count() >= 1) // 1/60√ 
        {
            fpsTimer = steady_clock::now();

            if (goPositive)
            {
                gameData.obstacle.positionX += gameData.obstacle.speed * duration_cast<sec>(FPS).count();
            }
            else
            {
                gameData.obstacle.positionX -= gameData.obstacle.speed * duration_cast<sec>(FPS).count();
            }
            
            if (gameData.obstacle.positionX > maxX || gameData.obstacle.positionX < minX)
            {
                gameData.obstacle.positionX > maxX ? gameData.obstacle.positionX = maxX : gameData.obstacle.positionX = minX;
                goPositive = !goPositive;
                cout << "MatchRoom: " << gameData.matchRoom << " | ObsID: " << gameData.obstacle.obstacleID << " | posX: " << gameData.obstacle.positionX << endl;
                npcServer.PostWrite(gameData);
            }
        }
    }
}

void ObstacleThread::RotationObstacle()
{
    time_point<steady_clock> fpsTimer(steady_clock::now());
    frame FPS{};

    while (true)
    {
        FPS = duration_cast<frame>(steady_clock::now() - fpsTimer);
        if (FPS.count() >= 1)
        {
            fpsTimer = steady_clock::now();

            gameData.obstacle.rotationZ += gameData.obstacle.speed * duration_cast<sec>(FPS).count() / 0.01f;
            if (gameData.obstacle.rotationZ > 180)
            {
                gameData.obstacle.rotationZ = -180;
                cout << "MatchRoom: " << gameData.matchRoom << " | rotZ: " << gameData.obstacle.positionX << endl;
                npcServer.PostWrite(gameData);
            }
        }
    }
}
