#include "pch.h"
#include "PacketHandler.h"
#include "MatchManager.h"
#include "MatchSession.h"
#include "Player.h"

void PacketHandler::HandlerPacket(PacketSessionRef& ref, BYTE* buffer, int32 len)
{
    PacketHeader* head = reinterpret_cast<PacketHeader*>(buffer);
    switch (head->type)
    {
    case Protocol::C_LOGIN:
        HandlerLogin(ref, ParsingPacket<Protocol::S_DATA>(buffer, (int32)head->size));
        break;
    default:
        break;
    }
}

void PacketHandler::HandlerLogin(PacketSessionRef& ref, Protocol::S_DATA&& pkt)
{
    MatchSessionRef _ref = static_pointer_cast<MatchSession>(ref);

    PlayerRef player = make_shared<Player>();
    player->ownerSession = _ref;
    player->playerId = pkt.id();
    int32 index = pkt.maplevel();

    GMatch->DoAsync(&MatchManager::MatchEnter, player, index);

    _ref->Send(MakeSendBuffer(pkt, Protocol::S_LOGIN));
}

SendBufferRef PacketHandler::MakeSendBuffer(Protocol::S_DATA pkt, Protocol::STATE type)
{
    return _MakeSendBuffer(pkt, type);
}
