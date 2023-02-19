using Google.Protobuf.Protocol;
using System;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using Cinemachine;


/*
 게임 오브젝트를 관리
 게임 오브젝트간의 충돌 관리??

 */
public class ObjectManager
{
    public MyPlayerController MyPlayer { get;  set; }
    public CameraController cameraController { get; set; }
    static ObjectManager _instance = new ObjectManager();
    public static ObjectManager Instance { get { return _instance; } }

    public Int64 myPlayerId = -1;
    //플레이어 정보 저장
    Dictionary<Int64, GameObject>               obstacle = new Dictionary<Int64, GameObject>();
    Dictionary<Int64, GameObject>               players = new Dictionary<Int64, GameObject>();
    Dictionary<Int64, ObstacleController>       shapes = new Dictionary<Int64, ObstacleController>();


    //추가
    public void AddPlayer(Int64 id, Player player)
    {
        GameObject go = Managers.Resource.Instantiate("Creature/Player");
        go.name = "Player" + id;

        players.Add(player.Id, go);

       //Debug.Log(players.Count);

        PlayerController pc = go.GetComponent<PlayerController>();
        pc.playerId = id;
        pc.playerInfo = player;
        pc.isStarted = true;
        Debug.Log(player.Position.X + " " + player.Position.Y + " " + player.Position.Z + " ");
        Debug.Log(player.Rotation.X + " " + player.Rotation.Y + " " + player.Rotation.Z + " ");
    }
    public void AddMyPlayer(Int64 id, Player player)
    {
        GameObject go = Managers.Resource.Instantiate("Creature/MyPlayer");
        go.name = "MyPlayer" + id;

        myPlayerId = id;
        players.Add(player.Id, go);

        MyPlayer = go.GetComponent<MyPlayerController>();
        MyPlayer.playerId = player.Id;
        MyPlayer.playerInfo = player;
        // Debug.Log(player.Position.X + " " + player.Position.Y + " " + player.Position.Z + " ");

        try
        {
            MyPlayer.spawnPoint.x = player.Position.X;
            MyPlayer.spawnPoint.y = player.Position.Y;
            MyPlayer.spawnPoint.z = player.Position.Z;
            MyPlayer.isStarted = true;
        }
        catch (Exception e)
        {
            MyPlayer.gameObject.transform.position = new Vector3(0.1f, 0.2f, 29f);
            MyPlayer.gameObject.transform.rotation = Quaternion.Euler(0, 180, 0);
            Debug.Log("Connect Game MyPlayer");
        }

        FindCamera(id, player);

        
    }

    public void FindCamera(Int64 id, Player player)
    {
        GameObject go = GameObject.Find("Virtual Camera");

        if (go == null)
            return;

        cameraController = go.GetComponent<CameraController>();
        cameraController.SetFollowTarget(players[player.Id]);
        

    }
   

    public void RemovePlayer(Int64 id)
    {
        players.Remove(id);
    }

    //삭제
    public void AddObtacle(Int64 id, Int32 shape, Obtacle obtacle)
    {
        Vector3 tempVec = new Vector3(obtacle.Position.X, obtacle.Position.Y, obtacle.Position.Z);
        Quaternion tempRot = Quaternion.Euler(obtacle.Rotation.X, obtacle.Rotation.Y, obtacle.Rotation.Z);
        GameObject go = null;
        switch (shape)
        {
            case 0:
                go = Managers.Resource.Instantiate("Trap/Sphere", tempVec, tempRot);
                UnityEngine.Debug.Log(0 + " Obtacle");
                go.name = "Obstacle" + id;
                obstacle.Add(id, go);

                TrapController tc = go.GetComponent<TrapController>();
                tc.id = id;
                tc.PosInfo = obtacle.Position;
                tc.RotInfo = obtacle.Rotation;
                tc.speed = obtacle.Speed;
                shapes.Add(id, tc);
                break;
            case 1:
                go = Managers.Resource.Instantiate("Trap/MovePlatform", tempVec, tempRot);
                UnityEngine.Debug.Log(1 + " Obtacle");
                go.name = "Obstacle" + id;
                obstacle.Add(id, go);

                PlatformController pc = go.GetComponent<PlatformController>();
                pc.id = id;
                pc.PosInfo = obtacle.Position;
                pc.RotInfo = obtacle.Rotation;
                pc.speed = obtacle.Speed;
                pc.direct = obtacle.Direction;

                shapes.Add(id, pc);
                break;
            case 2:
                go = Managers.Resource.Instantiate("Trap/Cylinder", tempVec, tempRot);
                UnityEngine.Debug.Log(2 + " Obtacle");
                go.name = "Obstacle" + id;
                obstacle.Add(id, go);

                RotatingTrapController rc = go.GetComponent<RotatingTrapController>();
                rc.id = id;
                rc.PosInfo = obtacle.Position;
                rc.RotInfo = obtacle.Rotation;
                rc.speed = obtacle.Speed;
                rc.direct = obtacle.Direction;

                shapes.Add(id, rc);
                break;
            default:
                break;
        }
    }
    public void RemoveObtacle(Int64 id)
    {
        obstacle.Remove(id);
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
        if (obstacle.TryGetValue(id, out obtacle))
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

    public void ClearPlaayers()
    {
        players.Clear();
    }

    public void ClearObstacle()
    {
        obstacle.Clear();
    }

    public void ClearShape()
    {
        shapes.Clear();
    }
}
