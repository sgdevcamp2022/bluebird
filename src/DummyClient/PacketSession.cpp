#include "pch.h"
#include "PacketSession.h"

PacketSession::PacketSession()
{

}

PacketSession::~PacketSession()
{

}
int32 PacketSession::OnRecv(BYTE* buffer, int32 len)
{
		// 패킷 조립 성공
	OnRecvPacket(buffer, len);

	return len;
}