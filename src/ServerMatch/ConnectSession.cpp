#include "pch.h"
#include "ConnectSession.h"
#include "MatchManager.h"

void ConnectSession::OnConnected()
{
	cout << "Connect" << endl;
	GMatch->ConnectGameServer(static_pointer_cast<ConnectSession>(shared_from_this()));
}

void ConnectSession::OnDisconnected()
{

}

void ConnectSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	
}

void ConnectSession::OnSend(int32 len)
{

}
