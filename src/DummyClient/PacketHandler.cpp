#include "pch.h"
#include "PacketHandler.h"

void PacketHandler::HandlerPacket(SessionRef ref, BYTE* buffer, int32 len)
{
    Pkt_Header* head = reinterpret_cast<Pkt_Header*>(buffer);
    switch (head->type)
    {
    case Protocol::MATCH_LOGIN :
        HandlerLogin(ref, ParsingPacket<Protocol::S_DATA>(buffer, (int32)head->size));
        break;
    default:
        break;
    }
}

void PacketHandler::HandlerLogin(SessionRef ref, Protocol::S_DATA&& pkt)
{
    cout << pkt.id() << " " << pkt.maplevel() << endl;
    ref->Send(MakeSendBuffer(pkt, Protocol::MATCH_LOGIN));
}

SendBufferRef PacketHandler::MakeSendBuffer(Protocol::S_DATA ptr, Protocol::STATE type)
{
    return _MakeSendBuffer(ptr, type);
}
