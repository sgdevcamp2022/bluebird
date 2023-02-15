using Google.Protobuf;
using Google.Protobuf.Protocol;
using ServerCore;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Net;
using System.Runtime.InteropServices;
using UnityEngine;

public class ServerSession : PacketSession
{
	public void Send(IMessage packet, INGAME type)
	{
        Pkt_Head head = new Pkt_Head();
        head.type = type;

        //마샬링에 필요한 만큼의 개체 크기를 반환
        int size = Marshal.SizeOf<Pkt_Head>();

        //Pkt_Head.size = data의 사이즈
        //패킷 사이즈 = head 사이즈 + data 사이즈
        head.size = (uint)packet.CalculateSize();
        byte[] send_buffer = new byte[head.size + size];

        IntPtr ptr = Marshal.AllocHGlobal(size);
        Marshal.StructureToPtr(head, ptr, true);
        Marshal.Copy(ptr, send_buffer, 0, size);
        Marshal.FreeHGlobal(ptr);

        //pkt값을 send_buffer에 복사?
        Array.Copy(packet.ToByteArray(), 0, send_buffer, size, head.size);

        Send(send_buffer);
    }

    
	public override void OnConnected(EndPoint endPoint)
	{
		Debug.Log($"OnConnected : {endPoint}");

        PacketManager.Instance.customHandler = (i, m) =>
        {
            PacketQueue.Instance.Push(i, m);
        };

        //ConnectData dataPkt;
        //dataPkt = new ConnectData()
        //{
        //    Id = 1,
        //    Level = 0,
        //    Room = 2,
        //};

        //ConnectData dataPkt;
        //System.Random rand = new System.Random();
        //try
        //{
        //    dataPkt = new ConnectData()
        //    {
        //        Id = PlayerInfo.playerInfo.userNo,
        //        Level = PlayerInfo.playerInfo.level,
        //        Room = PlayerInfo.playerInfo.room,
        //        //Player = {new Player {X = 0,Y=0,Z=0 } }
        //    };
        //}
        //catch (Exception e)
        //{
        //    dataPkt = new ConnectData()
        //    {
        //        Id = rand.Next(100),
        //        Level = 2,
        //        Room = 0,
        //        //Player = {new Player {X = 0,Y=0,Z=0 } }
        //    };
        //}

        System.Random rand = new System.Random();
        ConnectData dataPkt = new ConnectData()
        {
            Id = rand.Next(100),
            Level = 2,
            Room = 0,
            //Player = {new Player {X = 0,Y=0,Z=0 } }
        };

        Send(dataPkt, INGAME.Connect);
        Debug.Log("try connection..." + dataPkt.Id);
    }

	public override void OnDisconnected(EndPoint endPoint)
	{
		Debug.Log($"OnDisconnected : {endPoint}");
        //TODO
	}

	public override void OnRecvPacket(ArraySegment<byte> buffer, Pkt_Head head)
	{
		PacketManager.Instance.OnReceievePacket(buffer.Array, head);
	}

	public override void OnSend(int numOfBytes)
	{
		//Console.WriteLine($"Transferred bytes: {numOfBytes}");
	}
}