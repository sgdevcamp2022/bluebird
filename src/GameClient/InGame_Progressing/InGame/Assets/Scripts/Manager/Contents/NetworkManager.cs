using ServerCore;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Net;
using UnityEngine;
using Google.Protobuf;
using Google.Protobuf.Protocol;

public class NetworkManager
{
	ServerSession _session = new ServerSession();

	public void Send(ArraySegment<byte> sendBuff)
	{
		_session.Send(sendBuff);
	}

	public void Init()
	{
        string mIp = "127.0.0.1";
        IPAddress ipAddress = IPAddress.Parse(mIp);
        IPEndPoint endPoint = new IPEndPoint(ipAddress, 5000);

		Connector connector = new Connector();

		connector.Connect(endPoint,
			() => { return _session; },
			1);
	}

	public void Update()
	{
        //큐에 있는 패킷을 리스트로 옮긴다.
		List<PacketMessage> list = PacketQueue.Instance.PopAll();
		foreach (PacketMessage packet in list)
		{
			Action<IMessage> handler = PacketManager.Instance.GetHandler(packet.Id);
			if (handler != null)
				handler.Invoke(packet.Message);
		}	
	}

}
