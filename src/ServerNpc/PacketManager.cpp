#include "PacketManager.h"

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
        obsData->set_x(loginData.obstacle[i].obstacleX);
        obsData->set_y(loginData.obstacle[i].obstacleY);
        obsData->set_z(loginData.obstacle[i].obstacleZ);
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
    npcGameData.set_obstaclesize(gameData.obstacle.size());
    for (int i = 0; i < gameData.obstacle.size(); i++)
    {
        Npc::Obstacle* obsData = npcGameData.add_obstacle();
        obsData->set_id(gameData.obstacle[i].obstacleID);
        obsData->set_shape(gameData.obstacle[i].obstacleShape);
        obsData->set_x(gameData.obstacle[i].obstacleX);
        obsData->set_y(gameData.obstacle[i].obstacleY);
        obsData->set_z(gameData.obstacle[i].obstacleZ);
    }

    bufSize = headerSize + npcGameData.ByteSizeLong();

    //protobuf::uint8* outputBuf = new protobuf::uint8[bufSize];
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

void PacketManager::GetField(LoginData* loginData, ::google::protobuf::Message& msg, int index)
{
    const google::protobuf::Reflection* refl = msg.GetReflection();
    const google::protobuf::Descriptor* desc = msg.GetDescriptor();
    int fieldCnt = desc->field_count();
    //cout << "Message Name: " << desc->full_name().c_str() << endl;
    for (int i = 0; i < fieldCnt; i++)
    {
        
        const google::protobuf::FieldDescriptor* field = desc->field(i);
        string fieldName = field->name();
        //cout << "Field Name: " << field->name() << endl;
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

    //SQL 연동해서 id, x, y, z, shape 값 가져오기
    for (int i = 0; i < 2; i++)
    {
        Obstacle tempObs;
        tempObs.obstacleID = i+1;
        tempObs.obstacleShape = 1;
        tempObs.obstacleX = 10;
        tempObs.obstacleY = 20;
        tempObs.obstacleZ = 10;
        loginData->obstacle.push_back(tempObs);
    }
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
            PrintMsg(packet);
            break;
        }

        case Npc::LOGIN:
        {
            Npc::LoginData packet;
            if (packet.ParseFromCodedStream(&payload_input_stream) == false) break;
            returnValue = 1;
            //repeated 테스트용 패킷
            /*
            Npc::Obstacle* obsData = packet.add_obstacle();
            obsData->set_id(0);
            obsData->set_shape(0);
            obsData->set_x(0);
            obsData->set_y(0);
            obsData->set_z(0);
            */
            //
            GetField(loginData, packet);
            PrintMsg(packet);
            break;
        }

        default:
            cout << "Wrong Packet" << endl;
            break;
        }
    }
    return returnValue;
}
