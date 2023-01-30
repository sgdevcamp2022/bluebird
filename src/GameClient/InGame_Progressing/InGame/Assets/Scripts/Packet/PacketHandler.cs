using Google.Protobuf;
using Google.Protobuf.Protocol;
using ServerCore;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

class PacketHandler
{
	public static void S_ChatHandler(PacketSession session, IMessage packet)
	{
		Data chatPacket = packet as Data;
		ServerSession serverSession = session as ServerSession;

		Debug.Log(chatPacket.Id);
	}


}
