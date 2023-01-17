#pragma once
class ConnectSession : public PacketSession
{
public:
	ConnectSession() {}
	~ConnectSession()
	{
		cout << "~ConectSession" << endl;
	}
	virtual void OnConnected() override;
	virtual void OnDisconnected() override;
	virtual void OnRecvPacket(BYTE* buffer, int32 len) override;
	virtual void OnSend(int32 len) override;
};

