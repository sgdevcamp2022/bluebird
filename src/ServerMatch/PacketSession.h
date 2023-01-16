#pragma once

class PacketSession : public Session
{
public:
	PacketSession();
	virtual ~PacketSession();

protected:
	virtual int32	OnRecv(BYTE* buffer, int32 len) sealed;
	virtual void	OnRecvPacket(BYTE* buffer, int32 len) abstract;
};