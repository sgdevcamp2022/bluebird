using Google.Protobuf.Protocol;
using System;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;


/*
 게임 오브젝트를 관리
 게임 오브젝트간의 충돌 관리??

 */
public class ObjectManager
{
    public MyPlayerController MyPlayer { get;  set; }
    static ObjectManager _instance = new ObjectManager();
    public static ObjectManager Instance { get { return _instance; } }

    //플레이어 정보 저장
    Dictionary<Int64, GameObject>               obtacles = new Dictionary<Int64, GameObject>();
    Dictionary<Int64, GameObject>               players = new Dictionary<Int64, GameObject>();
    Dictionary<Int64, ObstacleController>       shapes = new Dictionary<Int64, ObstacleController>();


    //추가
    public void AddPlayer(Int64 id, Player player)
    {
        GameObject go = Managers.Resource.Instantiate("Creature/Player");
        go.name = "Player" + id;
;
        players.Add(player.Id, go);

       // Debug.Log(players.Count);

        PlayerController pc = go.GetComponent<PlayerController>();
        pc.id = id;
        pc.playerInfo = player;
        Debug.Log(player.Position.X + " " + player.Position.Y + " " + player.Position.Z + " ");
    }
    public void AddMyPlayer(Int64 id, Player player)
    {
        GameObject go = Managers.Resource.Instantiate("Creature/MyPlayer");
        go.name = "MyPlayer" + player.Id;
     

        players.Add(player.Id, go);

        MyPlayer = go.GetComponent<MyPlayerController>();
        MyPlayer.id = player.Id;
        MyPlayer.playerInfo = player;
        Debug.Log(player.Position.X + " " + player.Position.Y + " " + player.Position.Z + " ");
    }

    public void AddMyCamera(Int64 id, Player player)
    {
        GameObject go = Managers.Resource.Instantiate("Camera/MyCamera");
        go.name = "MyCamera" + player.Id;

        Debug.Log("My virtual Camera Created");
    }


    public void RemovePlayer(Int64 id)
    {
        players.Remove(id);
    }

    //삭제
    public void AddObtacle(Int64 id, Int32 shape, Obtacle obtacle)
    {
        GameObject go = null;
        switch (shape)
        {
            case 0:
                go = Managers.Resource.Instantiate("Trap/Sphere");
                UnityEngine.Debug.Log(0 + " Obtacle");
                go.name = "Obstacle" + id;
                obtacles.Add(id, go);

                TrapController tc = go.GetComponent<TrapController>();
                tc.id = id;
                tc.PosInfo = obtacle.Position;
                tc.RotInfo = obtacle.Rotation;
                tc.speed = obtacle.Speed;
                shapes.Add(id, tc);
                break;
            case 1:
                go = Managers.Resource.Instantiate("Trap/Cube");
                UnityEngine.Debug.Log(1 + " Obtacle");
                go.name = "Obstacle" + id;
                obtacles.Add(id, go);

                PlatformController pc = go.GetComponent<PlatformController>();
                pc.id = id;
                pc.PosInfo = obtacle.Position;
                pc.RotInfo = obtacle.Rotation;
                pc.speed = obtacle.Speed;
                shapes.Add(id, pc);
                break;
            case 2:
                go = Managers.Resource.Instantiate("Trap/Cylinder");
                UnityEngine.Debug.Log(2 + " Obtacle");
                go.name = "Obstacle" + id;
                obtacles.Add(id, go);

                RotatingTrapController rc = go.GetComponent<RotatingTrapController>();
                rc.id = id;
                rc.PosInfo = obtacle.Position;
                rc.RotInfo = obtacle.Rotation;
                rc.speed = obtacle.Speed;
                shapes.Add(id, rc);
                break;
            default:
                break;
        }
    }
    public void RemoveObtacle(Int64 id)
    {
        obtacles.Remove(id);
    }

    // 저장된 정보 리턴
    public GameObject GetPlayer(Int64 id)
    {
        GameObject player;
        if (players.TryGetValue(id, out player))
            return player;
        return null;
    }
    public GameObject GetObtacle(Int64 id)
    {
        GameObject obtacle;
        if (obtacles.TryGetValue(id, out obtacle))
            return obtacle;
        return null;
    }
    public ObstacleController GetObtacleController(Int64 id)
    {
        ObstacleController obtacle;
        if (shapes.TryGetValue(id, out obtacle))
            return obtacle;
        return null;
    }
}
