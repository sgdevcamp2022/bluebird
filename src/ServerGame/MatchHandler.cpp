#include "pch.h"
#include "MatchHandler.h"
#include "Games.h"
#include "GameObject.h"

void MatchHandler::HandlerPacket(PacketSessionRef& ref, BYTE* buffer, int32 len)
{
    MatchHeader* head = reinterpret_cast<MatchHeader*>(buffer);
    switch (head->type)
    {
    case Match::S_MATCH:
        HandlerMatch(ref, ParsingPacket<Match::S_Match, MatchHeader>(buffer, (int32)head->size));
        break;
    default:
        break;
    }
}

void MatchHandler::HandlerMatch(PacketSessionRef& ref, Match::S_Match&& pkt)
{
    // TODO 오류체크 : 이 사람이 제대로 매치메이킹 되어있는지 확인할 필요 존재
    // Redis로 판별해도 괜찮을 듯
    vector<PlayerRef> players;
    cout << pkt.level() << " " << pkt.ids_size() << " INSIDE : ";
    for (int i = 0; i < pkt.ids_size(); i++) {
        cout << pkt.ids(i) << " ";
    }
    cout << endl;
    for (int i = 0; i < pkt.ids_size(); i++) {
        auto data = pkt.ids(i);
        players.emplace_back(make_shared<Player>(data, pkt.room()));
    }
    Ggames->DoAsync(&Games::NewGame, std::move(players), pkt.level(), pkt.room());
    Ggames->DoTimer(8000, &Games::StartGame, pkt.room());
    //NPC 서버 테스트용 코드

    auto _ref = Ggames->GetNpcRef();
    if (_ref != nullptr) {
        Npc::LoginData data;
        data.set_maplevel(pkt.level());
        data.set_matchroom(pkt.room());

        _ref->Send(NpcHandler::MakeSendBuffer(data, Npc::LOGIN));
    }
}

SendBufferRef MatchHandler::MakeSendBuffer(Match::S_Match pkt, Match::STATE type)
{
    return _MakeSendBuffer<Match::S_Match, MatchHeader, Match::STATE>(pkt, type);
}
