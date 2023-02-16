#pragma once
class ConnectSession : public Sessions
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

