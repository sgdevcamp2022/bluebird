#include "pch.h"
#include "MatchSession.h"

void MatchSession::OnConnected()
{
    this_thread::sleep_for(1s);
    atomic<int32> th = 0;
    for (int i = 1; i <= 7; i++) {
        for (int j = 0; j < 10; j++) {
            Match::C_Login pkt;
            pkt.set_id(th.fetch_add(1));
            pkt.set_level(i);
            auto ref = PacketHandler::MakeSendBuffer(pkt, Match::C_LOGIN);
            Send(ref);
        }
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
