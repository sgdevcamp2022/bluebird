using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using StackExchange.Redis;


public class PlayerInfo : MonoBehaviour
{
    public IDatabase redis;
    
    public enum Status
    {
        LOBBY, MATCH, INGAME
    }
    public int userNo;
    public int room;
    public int level;
    public Status status = Status.LOBBY;

    public static PlayerInfo playerInfo;
    private void Awake()
    {
        playerInfo = this;
    }

    // Start is called before the first frame update
    void Start()
    {
        ConnectRedis();
        redis.HashSet(userNo.ToString(), "status", status.ToString());
        DontDestroyOnLoad(this.gameObject);
    }

    void ConnectRedis()
    {
        var option = ConfigurationOptions.Parse("34.84.148.50:6379");
        option.Password = "a12b34";
        var conn = ConnectionMultiplexer.Connect(option);
        redis = conn.GetDatabase();
    }
}
