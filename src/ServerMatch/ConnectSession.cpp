#include "pch.h"
#include "ConnectSession.h"

void ConnectSession::OnConnected()
{
	cout << "Connect" << endl;
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
