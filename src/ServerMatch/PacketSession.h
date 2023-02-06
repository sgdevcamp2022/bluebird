#pragma once

class PacketSession : public Session
{
public:
	PacketSession();
	virtual ~PacketSession();

private:
	string str;

protected:
	virtual int32	OnRecv(BYTE* buffer, int32 len) sealed;
	virtual void	OnRecvPacket(BYTE* buffer, Match::Header&&) abstract;
};

class Sessions : public Session
{
public:
	Sessions();
	virtual ~Sessions();

private:
	string str;

protected:
	virtual int32	OnRecv(BYTE* buffer, int32 len) sealed;
	virtual void	OnRecvPacket(BYTE* buffer, int32 len) abstract;
};