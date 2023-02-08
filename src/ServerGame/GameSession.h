#pragma once

class GameSession : public PacketSession
{
public:
	GameSession() { }
	~GameSession()
	{
		cout << "~GameSession" << endl;
	}
	virtual void OnConnected() override;
	virtual void OnDisconnected() override;
	virtual void OnRecvPacket(BYTE* buffer, int32 len) override;
	virtual void OnSend(int32 len) override;

public:
	PlayerRef				_mySelf = nullptr;
	weak_ptr<class Room>	_room;
	bool					_start = false;
};

