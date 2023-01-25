#pragma once
#pragma comment(lib, "ws2_32")

#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/text_format.h>
#include "ProtocolNpc.pb.h"
#include <WinSock2.h>
#include <string>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#undef GetMessage

using namespace google;
using namespace std;

struct MessageHeader
{
    protobuf::uint32 size;
    Npc::INGAME type;
    //Protocol::INGAME type;
};

class PacketManager
{
public:
    PacketManager() {}
    char* MakePacket(int header);
    //~PacketManager();
    int GetBufSize();
    int PacketProcess(protobuf::io::CodedInputStream& input_stream);

private:
    void PrintMsg(::google::protobuf::Message& msg);
    void WriteMessageToStream(Npc::INGAME msgType, const protobuf::Message& message,
        protobuf::io::CodedOutputStream& stream);
    const int headerSize = sizeof(MessageHeader);
    int bufSize = 0;
};