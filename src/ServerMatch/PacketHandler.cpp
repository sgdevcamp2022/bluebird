#include "pch.h"
#include "PacketHandler.h"
#include "MatchManager.h"
#include "MatchSession.h"

void PacketHandler::HandlerPacket(PacketSessionRef& ref, BYTE* buffer, Match::Header&& head)
{
    switch (head.state())
    {
    case Match::C_LOGIN:
        HandlerLogin(ref, ParsingPacket<Match::C_Login>(buffer, (int32)head.size()));
        break;
    case Match::C_CANCEL:
        HandlerCancle(ref, ParsingPacket<Match::C_Cancel>(buffer, (int32)head.size()));
        break;
    case Match::CHECK:
        HandlerCheck(ref, ParsingPacket<Match::Check>(buffer, (int32)head.size()));
        break;
    default:
        break;
    }
}

void PacketHandler::HandlerLogin(PacketSessionRef& ref, Match::C_Login&& pkt)
{
    MatchSessionRef _ref = static_pointer_cast<MatchSession>(ref);

    GMatch->DoAsync(&MatchManager::MatchEnter, pkt.id(), pkt.level());
}

void PacketHandler::HandlerCancle(PacketSessionRef& ref, Match::C_Cancel&& pkt)
{
    MatchSessionRef _ref = static_pointer_cast<MatchSession>(ref);
    GMatch->DoAsync(&MatchManager::MatchLeave, pkt.id(), pkt.level(), pkt.room());
}

void PacketHandler::HandlerCheck(PacketSessionRef& ref, Match::Check&& pkt)
{
    if (pkt.type() == 1) {
        GMatch->DoAsync(&MatchManager::ConnectMatchServer, static_pointer_cast<MatchSession>(ref));
    }
    else if(pkt.type() == -1) {
        GMatch->DoAsync(&MatchManager::ConnectLobyServer, static_pointer_cast<MatchSession>(ref));
    }
}

SendBufferRef PacketHandler::MakeSendBuffer(Match::S_Cancel pkt, Match::STATE type)
{
    return _MakeSendBuffer(pkt, type);
}

SendBufferRef PacketHandler::MakeSendBuffer(Match::S_Match pkt, Match::STATE type)
{
    return _MakeSendBuffer(pkt, type);
}


SendBufferRef PacketHandler::MakeSendBuffer(Match::S_Login pkt, Match::STATE type)
{
    return _MakeSendBuffer(pkt, type);
}

SendBufferRef PacketHandler::MakeSuccessBuffer(Match::S_Match pkt, Match::STATE type)
{
    return _Making<Match::S_Match, MatchHeader, Match::STATE>(pkt, type);
}
