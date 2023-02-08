#include "pch.h"
#include "PacketHandler.h"
#include "MatchManager.h"
#include "MatchSession.h"
#include "Player.h"

void PacketHandler::HandlerPacket(PacketSessionRef& ref, BYTE* buffer, Match::Header&& head)
{
    switch (head.state())
    {
    case Match::C_LOGIN:
        HandlerLogin(ref, ParsingPacket<Match::C_Login>(buffer, (int32)head.size()));
        break;
    case Match::C_CANCLE:
        HandlerCancle(ref, ParsingPacket<Match::C_Cancle>(buffer, (int32)head.size()));
        break;
    default:
        break;
    }
}

void PacketHandler::HandlerLogin(PacketSessionRef& ref, Match::C_Login&& pkt)
{
    MatchSessionRef _ref = static_pointer_cast<MatchSession>(ref);

    // TODO 오류체크 : 이 사람이 제대로 매치메이킹 되어있는지 확인할 필요 존재
    // Redis로 판별해도 괜찮을 듯
    PlayerRef player = make_shared<Player>();
    player->ownerSession = _ref;
    player->playerId = pkt.id();
    player->mapLevel = pkt.level();

    cout << "Login : " << pkt.id() << " " << pkt.level() << endl;

    GMatch->DoAsync(&MatchManager::MatchEnter, _ref, player, pkt.level());
}

void PacketHandler::HandlerCancle(PacketSessionRef& ref, Match::C_Cancle && pkt)
{
    MatchSessionRef _ref = static_pointer_cast<MatchSession>(ref);

    GMatch->DoAsync(&MatchManager::MatchLeave, pkt.id(), pkt.level(), pkt.room());
}

SendBufferRef PacketHandler::MakeSendBuffer(Match::S_Cancle pkt, Match::STATE type)
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
