#pragma once
#pragma comment(lib, "ws2_32")
#pragma comment(lib, "libmySQL.lib")

#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/text_format.h>
#include "ProtocolNpc.pb.h"
#include <WinSock2.h>
#include <string>
#include <vector>
#include <mysql.h>
#include <iostream>


#define _WINSOCK_DEPRECATED_NO_WARNINGS
#undef GetMessage

using namespace google;
using namespace std;

struct MessageHeader
{
    protobuf::uint32 size;
    Npc::INGAME type;
};

struct Obstacle
{
	int obstacleID;
	int obstacleShape;
	float positionX;
	float positionY;
	float positionZ;
	float rotationX;
	float rotationY;
	float rotationZ;
	float speed;
	float distance;
	int direction;
};

struct PlayerSpawn
{
	float positionX;
	float positionY;
	float positionZ;
	float rotationX;
	float rotationY;
	float rotationZ;
};

struct LoginData
{
	int mapLevel;
	int matchRoom;
	vector<Obstacle> obstacle;
	vector<PlayerSpawn> spawn;
};

struct StartData
{
	int room;
	int size;
	bool game;
};

struct GameData
{
	int matchRoom;
	Obstacle obstacle;
};

class ConnectToSQL
{
public:
	ConnectToSQL();
	~ConnectToSQL();

	int SQLInit();

	int ObstacleSQLQuery(const char* query, LoginData* loginData);
	int SpawnSQLQuery(const char* query, LoginData* loginData);

private:
	MYSQL Conn;
	MYSQL* ConnPtr;
	MYSQL_RES* Result;
	MYSQL_ROW Row;
	int Stat;
};

class PacketManager
{
public:
	PacketManager();
	char* MakeLoginPacket(LoginData loginData);
	char* MakeGamePacket(GameData gameData);
    //~PacketManager();
    int GetBufSize();
    int PacketProcess(LoginData* loginData, StartData* startData, protobuf::io::CodedInputStream& input_stream);

private:
    void PrintMsg(::google::protobuf::Message& msg);
	int GetField(LoginData* loginData, ::google::protobuf::Message& msg);
	int GetField(StartData* startData, ::google::protobuf::Message& msg);
    void WriteMessageToStream(Npc::INGAME msgType, const protobuf::Message& message,
        protobuf::io::CodedOutputStream& stream);
    const int headerSize = sizeof(MessageHeader);
    int bufSize = 0;
	ConnectToSQL* mysql;
};