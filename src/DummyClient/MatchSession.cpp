#include "pch.h"
#include "MatchSession.h"

void MatchSession::OnConnected()
{
    atomic<int32> th = 0;
    for (int i = 0; i < 5; i++) {
        Match::C_Login pkt;
        pkt.set_id(th.fetch_add(1));
        pkt.set_level(2);
        auto ref = PacketHandler::MakeSendBuffer(pkt, Match::C_LOGIN);
        Send(ref);
    }
}

void MatchSession::OnDisconnected()
{
   
}

void MatchSession::OnRecvPacket(BYTE* buffer, int32 len)
{
    string str;
    str.resize(4);
    memcpy(str.data(), buffer, 4);
    Match::Header header;
    header.ParseFromString(str);

    PacketSessionRef game_ref = static_pointer_cast<PacketSession>(shared_from_this());
    PacketHandler::HandlerPacket(game_ref, buffer, std::move(header));
}

void MatchSession::OnSend(int32 len)
{

}
