using Google.Protobuf.Protocol;
using System;
using System.Collections.Generic;

public class ObjectsManager
{
    static ObjectsManager _instance = new ObjectsManager();
    public static ObjectsManager Instance { get { return _instance; } }

    //플레이어 정보 저장
    Dictionary<Int64, Player> players = new Dictionary<Int64, Player>();
    Dictionary<Int64, Obtacle> obtacles = new Dictionary<Int64, Obtacle>();

    //추가
    public void AddPlayer(Int64 id, Player player)
    {
        players[id] = player;
    }
    public void RemovePlayer(Int64 id)
    {
        players.Remove(id);
    }

    //삭제
    public void AddObtacle(Int64 id, Obtacle obtacle)
    {
        obtacles[id] = obtacle;
    }
    public void RemoveObtacle(Int64 id)
    {
        obtacles.Remove(id);
    }

    // 저장된 정보 리턴
    public Player GetPlayer(Int64 id)
    {
        return players[id];
    }
    public Obtacle GetObtacle(Int64 id)
    {
        return obtacles[id];
    }
}
