#pragma once
class NpcSession : public PacketSession
{
public:
	NpcSession() { }
	~NpcSession() { }
	virtual void OnConnected() override;
	virtual void OnDisconnected() override;
	virtual void OnRecvPacket(BYTE* buffer, int32 len) override;
	virtual void OnSend(int32 len) override;
};
