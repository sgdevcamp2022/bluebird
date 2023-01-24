#include "PacketManager.h"

char* PacketManager::MakePacket(int id, float x, float y, float z)
{
    Npc::GameData gameData;
    gameData.set_matchroom(1);
    gameData.set_obstaclesize(2);
    for (int i = 0; i < 2; i++)
    {
        Npc::Obstacle* obsData = gameData.add_obstacle();
        obsData->set_id(10);
        obsData->set_x(10);
        obsData->set_y(20);
        obsData->set_z(30);
    }

    bufSize = headerSize + gameData.ByteSizeLong();
    //protobuf::uint8* outputBuf = new protobuf::uint8[bufSize];
    char* tempBuf = (char*)malloc(bufSize * sizeof(char));
    protobuf::io::ArrayOutputStream output_array_stream(tempBuf, bufSize);

    protobuf::io::CodedOutputStream output_coded_stream(&output_array_stream);

    WriteMessageToStream(Npc::GAME, gameData, output_coded_stream);

    return tempBuf;
}

void PacketManager::PrintMsg(::google::protobuf::Message& msg)
{
    string str;
    str = msg.DebugString();
    cout << str << endl;
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


int PacketManager::PacketProcess(protobuf::io::CodedInputStream& input_stream)
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
