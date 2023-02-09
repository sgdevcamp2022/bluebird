using Google.Protobuf;
using Google.Protobuf.Protocol;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using Unity.VisualScripting;
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
            if (Managers.Object.MyPlayer.playerId == player.Id)
                continue;
            Managers.Object.AddPlayer(player.Id, player);
            UnityEngine.Debug.Log(player.Id + " Inside");
        }
        foreach (Obtacle obtacle in data.Obtacle)
        {
            Managers.Object.AddObtacle(obtacle.Id, obtacle.Shape, obtacle);
            UnityEngine.Debug.Log("Object " + obtacle.Id + " Inside");
            UnityEngine.Debug.Log("ObjectRot " + obtacle.Rotation + " Inside");
        }
    }
    public static void ReConnect(IMessage packet)
    {
        Data data = packet as Data;
        foreach (Player player in data.Player)
        {
            //Player Spawn
            if (Managers.Object.myPlayerId == player.Id)
                Managers.Object.AddMyPlayer(player.Id, player);
            else
                Managers.Object.AddPlayer(player.Id, player);
            UnityEngine.Debug.Log(player.Id + " Inside");
        }
        foreach (Obtacle obtacle in data.Obtacle)
        {
            Managers.Object.AddObtacle(obtacle.Id, obtacle.Shape, obtacle);
            UnityEngine.Debug.Log("Object " + obtacle.Id + " Inside");
            UnityEngine.Debug.Log("ObjectRot " + obtacle.Rotation + " Inside");
        }
    }
    //카메라가 follow하는 프리펩 대상을 특정시켜주기
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

       
        pc.playerInfo.Position = data.Position;
        pc.playerInfo.Rotation = data.Rotation;
        
    }
    public static void ObtacleMove(IMessage packet)
    {
        Move data = packet as Move;
        ObstacleController go = Managers.Object.GetObtacleController(data.Id);
        go.PacketRecv = true;
        go.PosInfo = data.Position;
        go.RotInfo = data.Rotation;
    }
    public static void CnnectFail(IMessage packet)
    {
        Data data = packet as Data;
        if (data.Id == -1)
            UnityEngine.Debug.Log("Id Error");
        else if(data.MatchRoom == -1)
            UnityEngine.Debug.Log("Room Error");
    }
    public static void PlayerFail(IMessage packet)
    {
        Player player = packet as Player;
        // TODO 스폰 위치로 초기화 (패킷에 초기화 위치 넣어놨습니다)
        // 이후 player 패킷에 Position, Rotation 현 위치로 변경

        UnityEngine.Debug.Log("정상");
        if (Managers.Object.myPlayerId == player.Id)
        {
            Managers.Network.Send(player, INGAME.PlayerDrop);
        }
    }
    public static void GameComplete(IMessage packet)
    {
        GameCompleteData data = packet as GameCompleteData;
        UnityEngine.Debug.Log("GameComplte");
        //TODO
    }
    public static void PlayerGoal(IMessage packet)
    {
        PlayerGoalData data = packet as PlayerGoalData;
        UnityEngine.Debug.Log("PlayerGoal");
        // TODO
    }
}