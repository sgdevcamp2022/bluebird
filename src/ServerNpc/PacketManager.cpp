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
    for (int i = 0; i < loginData.spawn.size(); i++)
    {
        Npc::PlayerSpawn* spawnData = npcLoginData.add_spawn();
        spawnData->mutable_position()->set_x(loginData.spawn[i].positionX);
        spawnData->mutable_position()->set_y(loginData.spawn[i].positionY);
        spawnData->mutable_position()->set_z(loginData.spawn[i].positionZ);
        spawnData->mutable_rotation()->set_x(loginData.spawn[i].rotationX);
        spawnData->mutable_rotation()->set_y(loginData.spawn[i].rotationY);
        spawnData->mutable_rotation()->set_z(loginData.spawn[i].rotationZ);
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

int PacketManager::GetField(LoginData* loginData, ::google::protobuf::Message& msg)
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
            if (fieldName == "mapLevel" || fieldName == "level")
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
            else if (fieldName == "matchRoom" || fieldName == "room")
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
            else if (fieldName == "stage")
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
        }
    }

    string sql = "SELECT * FROM map" + (loginData->mapLevel > 9 ? to_string(loginData->mapLevel) : "0" + to_string(loginData->mapLevel));
    int state = mysql->ObstacleSQLQuery(sql.c_str(), loginData);
    if (state == 0)
    {
        cout << "SQL Query Error.." << endl;
        return 0;
    }
    sql += "spawn";
    state = mysql->SpawnSQLQuery(sql.c_str(), loginData);
    return state;
    
}

int PacketManager::GetField(StartData* startData, ::google::protobuf::Message& msg)
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
            if (fieldName == "room")
            {
                try
                {
                    startData->room = refl->GetInt32(msg, field);
                }
                catch (exception)
                {
                    startData->room = -1;
                }
            }
            else if (fieldName == "size")
            {
                try
                {
                    startData->size = refl->GetInt32(msg, field);
                }
                catch (exception)
                {
                    startData->size = -1;
                }
            }
        }
        else if (field->type() == google::protobuf::FieldDescriptor::TYPE_BOOL && !field->is_repeated())
        {
            if (fieldName == "game")
            {
                try
                {
                    startData->game = refl->GetBool(msg, field);
                }
                catch (exception)
                {
                    startData->game = false;
                }
            }
        }
    }
    return 2;

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


int PacketManager::PacketProcess(LoginData* loginData, StartData* startData, protobuf::io::CodedInputStream& input_stream)
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

        case Npc::START:
        {
            Npc::StartData packet;
            if (packet.ParseFromCodedStream(&payload_input_stream) == false) break;
            returnValue = GetField(startData, packet);
            break;
        }

        case Npc::NEXT:
        {
            Npc::NextStage packet;
            if (packet.ParseFromCodedStream(&payload_input_stream) == false) break;
            GetField(loginData, packet);
            returnValue = 3;
            break;
        }

        case Npc::END:
        {
            Npc::EndGame packet;
            if (packet.ParseFromCodedStream(&payload_input_stream) == false) break;
            GetField(loginData, packet);
            returnValue = 4;
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
    ConnPtr = mysql_real_connect(&Conn, "121.145.229.137", "root", "a12b34", "map", 3306, (char*)NULL, 0);

    if (ConnPtr == NULL)
    {
        cout << "Error : " << mysql_error(&Conn) << endl;
        return 0;
    }
    cout << "Success MySQL Init" << endl;
    return 1;
}

int ConnectToSQL::ObstacleSQLQuery(const char* query, LoginData* loginData)
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

int ConnectToSQL::SpawnSQLQuery(const char* query, LoginData* loginData)
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
        PlayerSpawn tempSpawn;
        tempSpawn.positionX = atof(Row[1]);
        tempSpawn.positionY = atof(Row[2]);
        tempSpawn.positionZ = atof(Row[3]);
        tempSpawn.rotationX = atof(Row[4]);
        tempSpawn.rotationY = atof(Row[5]);
        tempSpawn.rotationZ = atof(Row[6]);
        loginData->spawn.push_back(tempSpawn);
    }
    mysql_free_result(Result);
    return 1;
}
