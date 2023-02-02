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