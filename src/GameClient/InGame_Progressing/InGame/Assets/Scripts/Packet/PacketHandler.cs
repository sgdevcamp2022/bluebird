using Google.Protobuf;
using Google.Protobuf.Protocol;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
//using UnityEditor.Timeline.Actions;
using UnityEngine;

public class PacketHandler
{
    public static void GetTickCount(IMessage packet)
    {
        //TODO RTT구하기
        Times times = packet as Times;
        Managers.Network.RTT = times.Time;
    }

    public static void TimeSync(IMessage packet)
    {
        Times times = packet as Times;
        Managers.Network.TICK = times.Time;
        UnityEngine.Debug.Log("GetTime(" + times.Time + ") : " + Managers.Network.TICK + " : " + Managers.Network.RTT);
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
            Managers.Object.AddObtacle(obtacle.Id, obtacle.Shape, obtacle);
            UnityEngine.Debug.Log("Object " + obtacle.Id + " Inside");
        }

        Move move = new Move()
        {
            Id = Managers.Object.MyPlayer.id,
            Position = new Vector { X = 0, Y = 0, Z = 0 },
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
        GameObject go = Managers.Object.GetPlayer(data.Id);

        if (go == null)
            return;

        PlayerController pc = go.GetComponent<PlayerController>();

        if (pc == null)
            return;

        //pc.playerInfo.Id = data.Id;
        pc.playerInfo.Position = data.Position;
        pc.playerInfo.Rotation = data.Rotation;
        //pc.playerInfoUpdate();
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
    public static void CnnectFail(IMessage packet)
    {
        Data data = packet as Data;
        if (data.Id == -1)
            UnityEngine.Debug.Log("Id Error");
        else if(data.MatchRoom == -1)
            UnityEngine.Debug.Log("Room Error");
    }
}