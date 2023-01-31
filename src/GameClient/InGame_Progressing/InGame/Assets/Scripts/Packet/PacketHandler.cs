using Google.Protobuf;
using Google.Protobuf.Protocol;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

public class PacketHandler
{

    public static long[] playerid;
    public static bool same = false;
    

    public static void GameStart(IMessage packet)
    {
        Data data = packet as Data;
        foreach (Player player in data.Player)
        {
            //Player Spawn
            Managers.Object.AddPlayer(player.Id, player,false); 
            UnityEngine.Debug.Log(player.Id + " Inside");
        }
        foreach (Obtacle obtacle in data.Obtacle)
        {
            ObjectManager.Instance.AddObtacle(obtacle.Id, obtacle);
            UnityEngine.Debug.Log(obtacle.Id + " Inside");
        }
    }
    public static void GameConnect(IMessage packet)
    {
        Data data = packet as Data;
        Player player;
        if (same)
        {
            player = data.Player[1];
        }
        else
        {
            player = data.Player[0];
        }
 

        Managers.Object.AddPlayer(player.Id, player,true);

        same = true;

        UnityEngine.Debug.Log("Player connected..." + player.X + " " + player.Y + " " + player.Z);
    }
    public static void PlayerMove(IMessage packet)
    {
        Data data = packet as Data;
        Player user = data.Player[data.Player.Count - 1];

        Player player = ObjectManager.Instance.GetPlayer(data.Id);
        // 이동 로직 구현 매차 구챠
        //player.X = user.X; player.Y = user.Y;  player.Z = user.Z;
        UnityEngine.Debug.Log(user.Id + " " + user.X + " " + user.Y + " " + user.Z);
    }

    public static void ObtacleMove(IMessage packet)
    {
        Data data = packet as Data;
        Obtacle user = data.Obtacle[data.Obtacle.Count - 1];

        Player player = ObjectManager.Instance.GetPlayer(data.Id);
        // 이동 로직 구현 매차 구챠
        //player.X = user.X; player.Y = user.Y;  player.Z = user.Z;
        UnityEngine.Debug.Log(user.Id + " " + user.X + " " + user.Y + " " + user.Z);
    }
}