using Google.Protobuf;
using Google.Protobuf.Protocol;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using UnityEditor.Timeline.Actions;
using UnityEngine;

public class PacketHandler
{
    public static void GetTickCount(IMessage packet)
    {
        //TODO RTT구하기
        Times times = packet as Times;
        Managers.Network.RTT = (Managers.Network.GetTimeNow() - times.Time) / 2;
    }

    public static void GameStart(IMessage packet)
    {
        Data data = packet as Data;
        foreach (Player player in data.Player)
        {
            //Player Spawn
            if (Managers.Object.MyPlayer.id == player.Id)
                continue;
            Managers.Object.AddPlayer(player.Id, player);
            UnityEngine.Debug.Log(player.Id + " Inside");
        }
        foreach (Obtacle obtacle in data.Obtacle)
        {
            Managers.Object.AddObtacle(obtacle.Id, obtacle);
            UnityEngine.Debug.Log("Object " + obtacle.Id + " Inside");
        }

        Move move = new Move()
        {
            Id = Managers.Object.MyPlayer.id,
            Position = new Vector { X = 1, Y = 1, Z = 1 },
            Rotation = new Vector { X = 0, Y = 0, Z = 0 }
        };
        Managers.Network.Send(move, INGAME.PlayerMove);
    }
    public static void GameConnect(IMessage packet)
    {
        Player data = packet as Player;
        Managers.Object.AddMyPlayer(data.Id, data);

        UnityEngine.Debug.Log("Player connected... " + data.Id);
    }
    public static void PlayerMove(IMessage packet)
    {
        Move data = packet as Move;
        Player player = Managers.Object.GetPlayer(data.Id);
        // 이동 로직 구현 매차 구챠
        //player.X = user.X; player.Y = user.Y;  player.Z = user.Z;
        if(player != null)
        {
            Vector user = data.Position;
            UnityEngine.Debug.Log(data.Id + " " + user.X + " " + user.Y + " " + user.Z);
        }
    }

    public static void ObtacleMove(IMessage packet)
    {
        Data data = packet as Data;
        foreach(Obtacle obtacle in data.Obtacle)
        {
            GameObject go = Managers.Object.GetObtacle(obtacle.Id);
            if (go == null)
                continue;
            TrapController tc = go.GetComponent<TrapController>();
            if (tc == null)
                continue;
            tc.PosInfo = obtacle.Position;
        }
    }
}