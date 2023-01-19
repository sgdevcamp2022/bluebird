#include "pch.h"
#include "PacketHandler.h"
#include "MatchSession.h"

void PacketHandler::HandlerPacket(PacketSessionRef& ref, BYTE* buffer, int32 len)
{
   
    PacketHeader* head = reinterpret_cast<PacketHeader*>(buffer);
    switch (head->type)
    {
    case Match::S_LOGIN:
        HandlerLogin(ref, ParsingPacket<Match::Data>(buffer, (int32)head->size));
        break;
    case Match::S_MATCH:
        HandlerMatch(ref, ParsingPacket<Match::Success>(buffer, (int32)head->size));
        break;
    default:
        break;
    }
}

void PacketHandler::HandlerLogin(PacketSessionRef& ref, Match::Data&& pkt)
{
    cout << pkt.id() << " " << pkt.maplevel() << endl;
}

void PacketHandler::HandlerMatch(PacketSessionRef& ref, Match::Success&& pkt)
{
    cout << "MatchSuccess " << pkt.id() << " " << pkt.matchroom() << endl;
}

SendBufferRef PacketHandler::MakeSendBuffer(Match::Data pkt, Match::STATE type)
{
    return _MakeSendBuffer(pkt, type);
}