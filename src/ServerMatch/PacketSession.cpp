#include "pch.h"
#include "PacketSession.h"

PacketSession::PacketSession()
{
	str.resize(4);
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
		if (dataSize < 4)
			break;

		memcpy(str.data(), buffer, 4);
		Match::Header header;
		header.ParseFromString(str);
		// 헤더에 기록된 패킷 크기를 파싱할 수 있어야 한다
		if ((dataSize - 4) < header.size())
			break;
		
		// 패킷 조립 성공
		OnRecvPacket(&buffer[processLen], std::move(header));

		processLen += (header.size() + 4);
	}

	return processLen;
}

Sessions::Sessions()
{

}

Sessions::~Sessions()
{

}

int32 Sessions::OnRecv(BYTE* buffer, int32 len)
{
	int32 processLen = 0;

	while (true)
	{
		int32 dataSize = len - processLen;
		// 최소한 헤더는 파싱할 수 있어야 한다
		if (dataSize < sizeof(MatchHeader))
			break;

		MatchHeader header = *(reinterpret_cast<MatchHeader*>(&buffer[processLen]));

		// 헤더에 기록된 패킷 크기를 파싱할 수 있어야 한다
		if ((dataSize - sizeof(MatchHeader)) < header.size)
			break;

		// 패킷 조립 성공
		OnRecvPacket(&buffer[processLen], header.size);

		processLen += (header.size + sizeof(MatchHeader));
	}

	return processLen;
}