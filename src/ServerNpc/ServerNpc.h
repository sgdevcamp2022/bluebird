#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include "PacketManager.h"
#include <algorithm>
#include <list>
#include <chrono>
#include <cstdint>

using namespace std;
using namespace chrono;
using frame = duration<int32_t, ratio<1, 60>>;
using sec = duration<float>;

class ObstacleThread;

class ServerNpc
{
public:
    ServerNpc(boost::asio::io_context& io_service) :
        m_io_service(io_service), m_Socket(io_service), m_nSeqNumber(0) {}
    ~ServerNpc();

    void Connect(boost::asio::ip::tcp::endpoint& endpoint);
    void PostWrite(LoginData loginData);
    void PostWrite(GameData gameData);

    list<StartData>* GetStartData();
private:
    

    void PostReceive();

    void handle_connect(const boost::system::error_code& error);
    void handle_write(const boost::system::error_code& error, size_t bytes_transferred);
    void handle_receive(const boost::system::error_code& error, size_t bytes_transferred);

    void ThreadInterrupt(int matchRoom);

    boost::asio::io_context& m_io_service;
    boost::asio::ip::tcp::socket m_Socket;
    int m_nSeqNumber;
    char* outputBuf;
    char* inputBuf;
    int bufSize;
    array<char, 128> m_ReceiveBuffer;

    PacketManager* packetManager;

    list<pair<int, boost::thread*>> threadGroup;
    list<pair<int, boost::thread*>>::const_iterator iter;

    list<StartData> roomGroup;
    list<StartData>::const_iterator iterRoom;

    boost::mutex mutex;
};

class ObstacleThread
{
public:

    ObstacleThread(LoginData loginData, int index, ServerNpc& npcServer);
    void operator()();
    
private:
    void MovingObstacle();
    void RotationObstacle();

    ServerNpc& npcServer;
    LoginData loginData;
    GameData gameData;
    list<StartData>* roomGroup;
    list<StartData>::const_iterator iterRoom;
};
