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

    public static  Google.Protobuf.Protocol.Vector spawnPoint = new Vector { X = 0.1f, Y = 0.2f, Z = 29f };
    public static Google.Protobuf.Protocol.Vector spawnRotation = new Vector { X = 0f, Y = 180f, Z = 0f };
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

        GameObject go = GameObject.Find("GameScene");
        GameScene gs = go.GetComponent<GameScene>();
        gs.SetStartGame();

        GameObject go2 = GameObject.Find("GameManager");
        GameManager igm = go2.GetComponent<GameManager>();
        igm.GameStartTxt();


        UnityEngine.Debug.Log("Game Start!");
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
        pc.SetAnim(data.State);
        
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
        GameObject go = Managers.Object.GetPlayer(player.Id);

        if (go == null)
            return;

        PlayerController pc = go.GetComponent<PlayerController>();

        if (pc == null)
            return;

        pc.playerInfo.Position = spawnPoint;
        pc.playerInfo.Rotation = spawnRotation;
        pc.State = Define.BirdState.Idle;

        player.Position = spawnPoint;
        player.Rotation = spawnRotation;


            
        if (Managers.Object.myPlayerId == player.Id)
        {
            Managers.Network.Send(player, INGAME.PlayerDrop);
        }
    }
    public static void GameComplete(IMessage packet)
    {
        // TODO
        // bool 보고 성공인지 실패인지 판별해서 성공이면 다음 게임
        // 실패하면 로비로 넘어가게 만들면 될거 같습니다
        PlayerGoalData data = packet as PlayerGoalData;
        UnityEngine.Debug.Log("GameComplte");
        
    }
    public static void GameEnds(IMessage packet)
    {

        PlayerGoalData data = packet as PlayerGoalData;
        UnityEngine.Debug.Log("GameEnd");
    }
    public static void PlayerGoal(IMessage packet)
    {
        PlayerGoalData data = packet as PlayerGoalData;
        UnityEngine.Debug.Log("PlayerGoal");

        GameObject go = Managers.Object.GetPlayer(data.Id);
        PlayerController pc = go.GetComponent<PlayerController>();

        if (go == null)
            return;

        //안보이게 만들고, 비활성화 시키고 카메라를 관전 카메라로 전환??
        //don't destory on load 사용
        if (data.Success)
        {
            UnityEngine.Debug.Log("Goal Packet Arrived");
            pc.SetClearStageNum();
            pc.SetDestroy();

        }
        else
        {
            //pc.SetDestroy();
        }

    }
}