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
            cout << "Object ID: " << gameData.obstacle[i].obstacleID << endl;
            cout << "X: " << gameData.obstacle[i].obstacleX << " | Y: " << gameData.obstacle[i].obstacleY << " | Z: " << gameData.obstacle[i].obstacleZ << endl;
        }

        npcServer.PostWrite(gameData);
        boost::this_thread::sleep(boost::posix_time::seconds(1));
    }
}