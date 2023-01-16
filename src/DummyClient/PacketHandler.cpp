#include "pch.h"
#include "PacketHandler.h"
#include "MatchSession.h"

void PacketHandler::HandlerPacket(PacketSessionRef& ref, BYTE* buffer, int32 len)
{
   
    PacketHeader* head = reinterpret_cast<PacketHeader*>(buffer);
    switch (head->type)
    {
    case Protocol::S_LOGIN:
        HandlerLogin(ref, ParsingPacket<Protocol::DATA>(buffer, (int32)head->size));
        break;
    case Protocol::S_MATCH:
        HandlerMatch(ref, ParsingPacket<Protocol::DATA>(buffer, (int32)head->size));
        break;
    default:
        break;
    }
}

void PacketHandler::HandlerLogin(PacketSessionRef& ref, Protocol::DATA&& pkt)
{
    if(pkt.state())
        cout << pkt.id() << " " << pkt.maplevel() << endl;
}

void PacketHandler::HandlerMatch(PacketSessionRef& ref, Protocol::DATA&& pkt)
{
    cout << "MatchSuccess " << pkt.id() << " " << pkt.maplevel() << endl;
}

SendBufferRef PacketHandler::MakeSendBuffer(Protocol::DATA pkt, Protocol::STATE type)
{
    return _MakeSendBuffer(pkt, type);
}
