#include "PacketManager.h"

using namespace std;

PacketManager::PacketManager()
{
    mysql = new ConnectToSQL();
}

char* PacketManager::MakeLoginPacket(LoginData loginData)
{
    Npc::LoginData npcLoginData;

    npcLoginData.set_maplevel(loginData.mapLevel);
    npcLoginData.set_matchroom(loginData.matchRoom);
    for (int i = 0; i < loginData.obstacle.size(); i++)
    {
        Npc::Obstacle* obsData = npcLoginData.add_obstacle();
        obsData->set_id(loginData.obstacle[i].obstacleID);
        obsData->set_shape(loginData.obstacle[i].obstacleShape);
        obsData->mutable_position()->set_x(loginData.obstacle[i].positionX);
        obsData->mutable_position()->set_y(loginData.obstacle[i].positionY);
        obsData->mutable_position()->set_z(loginData.obstacle[i].positionZ);
        obsData->mutable_rotation()->set_x(loginData.obstacle[i].rotationX);
        obsData->mutable_rotation()->set_y(loginData.obstacle[i].rotationY);
        obsData->mutable_rotation()->set_z(loginData.obstacle[i].rotationZ);
        obsData->set_speed(loginData.obstacle[i].speed);
        obsData->set_direction(loginData.obstacle[i].direction);
    }

    bufSize = headerSize + npcLoginData.ByteSizeLong();

    //protobuf::uint8* outputBuf = new protobuf::uint8[bufSize];
    char* tempBuf = (char*)malloc(bufSize * sizeof(char));
    protobuf::io::ArrayOutputStream output_array_stream(tempBuf, bufSize);

    protobuf::io::CodedOutputStream output_coded_stream(&output_array_stream);

    WriteMessageToStream(Npc::LOGIN, npcLoginData, output_coded_stream);

    return tempBuf;
}

char* PacketManager::MakeGamePacket(GameData gameData)
{

    Npc::GameData npcGameData;
    npcGameData.set_matchroom(gameData.matchRoom);
    npcGameData.set_id(gameData.obstacle.obstacleID);
    npcGameData.set_shape(gameData.obstacle.obstacleShape);
    npcGameData.mutable_position()->set_x(gameData.obstacle.positionX);
    npcGameData.mutable_position()->set_y(gameData.obstacle.positionY);
    npcGameData.mutable_position()->set_z(gameData.obstacle.positionZ);
    npcGameData.mutable_rotation()->set_x(gameData.obstacle.rotationX);
    npcGameData.mutable_rotation()->set_y(gameData.obstacle.rotationY);
    npcGameData.mutable_rotation()->set_z(gameData.obstacle.rotationZ);

    bufSize = headerSize + npcGameData.ByteSizeLong();

    char* tempBuf = (char*)malloc(bufSize * sizeof(char));
    protobuf::io::ArrayOutputStream output_array_stream(tempBuf, bufSize);

    protobuf::io::CodedOutputStream output_coded_stream(&output_array_stream);

    WriteMessageToStream(Npc::GAME, npcGameData, output_coded_stream);

    return tempBuf;
}

void PacketManager::PrintMsg(::google::protobuf::Message& msg)
{
    string str;
    str = msg.DebugString();
    cout << str << endl;
}

int PacketManager::GetField(LoginData* loginData, ::google::protobuf::Message& msg, int index)
{
    const google::protobuf::Reflection* refl = msg.GetReflection();
    const google::protobuf::Descriptor* desc = msg.GetDescriptor();
    int fieldCnt = desc->field_count();
    for (int i = 0; i < fieldCnt; i++)
    {
        
        const google::protobuf::FieldDescriptor* field = desc->field(i);
        string fieldName = field->name();
        if (field->type() == google::protobuf::FieldDescriptor::TYPE_INT32 && !field->is_repeated())
        {
            if (fieldName == "mapLevel")
            {
                try
                {
                    loginData->mapLevel = refl->GetInt32(msg, field);
                }
                catch (exception)
                {
                    loginData->mapLevel = -1;
                }
            }
            else if (fieldName == "matchRoom")
            {
                try
                {
                    loginData->matchRoom = refl->GetInt32(msg, field);
                }
                catch (exception)
                {
                    loginData->matchRoom = -1;
                }
            }
        }
    }

    string sql = "SELECT * FROM map" + (loginData->mapLevel > 9 ? to_string(loginData->mapLevel) : "0" + to_string(loginData->mapLevel));
    return mysql->SQLQuery(sql.c_str(), loginData);
    
}

void PacketManager::WriteMessageToStream(Npc::INGAME msgType, const protobuf::Message& message,
    protobuf::io::CodedOutputStream& stream)
{
    MessageHeader msgHeader;
    msgHeader.size = message.ByteSizeLong();
    msgHeader.type = msgType;
    stream.WriteRaw(&msgHeader, sizeof(MessageHeader));
    message.SerializeToCodedStream(&stream);
}

int PacketManager::GetBufSize()
{
    return bufSize;
}


int PacketManager::PacketProcess(LoginData* loginData, protobuf::io::CodedInputStream& input_stream)
{
    int returnValue = 0;
    MessageHeader msgHeader;
    while (input_stream.ReadRaw(&msgHeader, headerSize))
    {
        const void* payload_ptr = NULL;
        int remainSize = 0;
        input_stream.GetDirectBufferPointer(&payload_ptr, &remainSize);
        if (remainSize < (signed)msgHeader.size) break;

        protobuf::io::ArrayInputStream payload_array_stream(payload_ptr, msgHeader.size);
        protobuf::io::CodedInputStream payload_input_stream(&payload_array_stream);
        input_stream.Skip(msgHeader.size);

        switch (msgHeader.type)
        {
        case Npc::GAME:
        {
            Npc::GameData packet;
            if (packet.ParseFromCodedStream(&payload_input_stream) == false) break;
            break;
        }

        case Npc::LOGIN:
        {
            Npc::LoginData packet;
            if (packet.ParseFromCodedStream(&payload_input_stream) == false) break;
            returnValue = GetField(loginData, packet);
            break;
        }

        default:
            cout << "Wrong Packet" << endl;
            break;
        }
    }
    return returnValue;
}



ConnectToSQL::ConnectToSQL()
{
    ConnPtr = nullptr;
    SQLInit();
}

ConnectToSQL::~ConnectToSQL()
{
    mysql_close(ConnPtr);
}

int ConnectToSQL::SQLInit()
{
    mysql_init(&Conn);
    ConnPtr = mysql_real_connect(&Conn, "127.0.0.1", "root", "Z797944z!", "map", 3306, (char*)NULL, 0);

    if (ConnPtr == NULL)
    {
        cout << "Error : " << mysql_error(&Conn) << endl;
        return 0;
    }
    cout << "Success MySQL Init" << endl;
    return 1;
}

int ConnectToSQL::SQLQuery(const char* query, LoginData* loginData)
{
    Stat = mysql_query(ConnPtr, query);
    if (Stat != 0)
    {
        cout << "Error : " << mysql_error(&Conn) << endl;
        return 0;
    }

    Result = mysql_store_result(ConnPtr);
    while ((Row = mysql_fetch_row(Result)) != NULL)
    {
        Obstacle tempObs;
        tempObs.obstacleID = atoi(Row[0]);
        tempObs.obstacleShape = atoi(Row[1]);
        tempObs.positionX = atof(Row[2]);
        tempObs.positionY = atof(Row[3]);
        tempObs.positionZ = atof(Row[4]);
        tempObs.rotationX = atof(Row[5]);
        tempObs.rotationY = atof(Row[6]);
        tempObs.rotationZ = atof(Row[7]);
        tempObs.speed = atof(Row[8]);
        tempObs.distance = atof(Row[9]);
        tempObs.direction = atoi(Row[10]);
        loginData->obstacle.push_back(tempObs);
    }
    mysql_free_result(Result);
    return 1;
}