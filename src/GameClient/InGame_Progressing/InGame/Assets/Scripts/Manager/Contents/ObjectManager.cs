using Google.Protobuf.Protocol;
using System;
using System.Collections.Generic;
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
    Dictionary<Int64, Player> players = new Dictionary<Int64, Player>();
    Dictionary<Int64, GameObject> obtacles = new Dictionary<Int64, GameObject>();
    Dictionary<Int64, GameObject> objects = new Dictionary<Int64, GameObject>();

    //추가
    public void AddPlayer(Int64 id, Player player)
    {
        GameObject go = Managers.Resource.Instantiate("Creature/Player");
        go.name = "Player" + id;

        players.Add(id, player);
        objects.Add(player.Id, go);

       // Debug.Log(players.Count);

        PlayerController pc = go.GetComponent<PlayerController>();
        pc.id = id;
        pc.playerInfo = player;
    }
    public void AddMyPlayer(Int64 id, Player player)
    {
        GameObject go = Managers.Resource.Instantiate("Creature/MyPlayer");
        go.name = "MyPlayer" + player.Id;

        players.Add(player.Id, player);
        objects.Add(player.Id, go);

        MyPlayer = go.GetComponent<MyPlayerController>();
        MyPlayer.id = player.Id;
        MyPlayer.playerInfo = player;
    }
    public void RemovePlayer(Int64 id)
    {
        players.Remove(id);
    }

    //삭제
    public void AddObtacle(Int64 id, Obtacle obtacle)
    {
        GameObject go = Managers.Resource.Instantiate("Trap/Sphere");
        go.name = "Obstacle" + id;
        obtacles.Add(id, go);

        TrapController tc = go.GetComponent<TrapController>();
        tc.id = id;
        tc.PosInfo = obtacle.Position;

      //  UnityEngine.Debug.Log(obtacles.Count);
    }
    public void RemoveObtacle(Int64 id)
    {
        obtacles.Remove(id);
    }

    // 저장된 정보 리턴
    public Player GetPlayer(Int64 id)
    {
        Player player;
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

    public GameObject FindById(Int64 id)
    {
        GameObject go = null;
        objects.TryGetValue(id, out go);
        return go;
    }
}
