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
	weak_ptr<class Player>	_mySelf;
	weak_ptr<class Room>	_room;
};

