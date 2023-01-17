#include "pch.h"
#include "PacketHandler.h"
#include "MatchSession.h"

void PacketHandler::HandlerPacket(PacketSessionRef& ref, BYTE* buffer, int32 len)
{
   
    PacketHeader* head = reinterpret_cast<PacketHeader*>(buffer);
    switch (head->type)
    {
    case Match::S_LOGIN:
        HandlerLogin(ref, ParsingPacket<Match::DATA>(buffer, (int32)head->size));
        break;
    case Match::S_MATCH:
        HandlerMatch(ref, ParsingPacket<Match::DATA>(buffer, (int32)head->size));
        break;
    default:
        break;
    }
}

void PacketHandler::HandlerLogin(PacketSessionRef& ref, Match::DATA&& pkt)
{
   
}

void PacketHandler::HandlerMatch(PacketSessionRef& ref, Match::DATA&& pkt)
{
    cout << "MatchSuccess " << pkt.id() << " " << pkt.maplevel() << endl;
}

SendBufferRef PacketHandler::MakeSendBuffer(Match::DATA pkt, Match::STATE type)
{
    return _MakeSendBuffer(pkt, type);
}
