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
	int32 processLen = 0;

	while (true)
	{
		int32 dataSize = len - processLen;
		// 최소한 헤더는 파싱할 수 있어야 한다
		if (dataSize < HEAD_SIZE)
			break;

		GameHeader header = *(reinterpret_cast<GameHeader*>(&buffer[processLen]));

		// 헤더에 기록된 패킷 크기를 파싱할 수 있어야 한다
		if ((dataSize - HEAD_SIZE) < header.size)
			break;

		int32 total = HEAD_SIZE + header.size;

		// 패킷 조립 성공
		OnRecvPacket(&buffer[processLen], total);

		processLen += total;
	}

	return processLen;
}