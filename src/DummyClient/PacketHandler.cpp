#include "pch.h"
#include "PacketHandler.h"
#include "MatchSession.h"

void PacketHandler::HandlerPacket(PacketSessionRef& ref, BYTE* buffer, Match::Header&& head)
{
    switch (head.state())
    {
    case Match::S_LOGIN:
        HandlerLogin(ref, ParsingPacket<Match::S_Login>(buffer, (int32)head.size()));
        break;
    case Match::S_MATCH:
        HandlerMatch(ref, ParsingPacket<Match::S_Match>(buffer, (int32)head.size()));
        break;
    default:
        break;
    }
}

SendBufferRef PacketHandler::MakeSendBuffer(Match::C_Login pkt, Match::STATE type)
{
    return _MakeSendBuffer(pkt, type);
}

SendBufferRef PacketHandler::MakeSendBuffer(Match::C_Cancle pkt, Match::STATE type)
{
    return _MakeSendBuffer(pkt, type);
}

void PacketHandler::HandlerLogin(PacketSessionRef& ref, Match::S_Login&& pkt)
{
    cout << "Inside : " << pkt.id() << " " << pkt.room() << endl;
}

void PacketHandler::HandlerMatch(PacketSessionRef& ref, Match::S_Match&& pkt)
{
    cout << "MatchSuccess ";
    for (int i = 0; i < pkt.ids_size(); i++) {
        cout << pkt.ids(i) << " ";
    }
    cout << "(" << pkt.room() << ")" << endl;
}