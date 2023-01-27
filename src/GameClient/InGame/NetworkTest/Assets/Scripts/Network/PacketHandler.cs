using Google.Protobuf;
using Google.Protobuf.Protocol;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class PacketHandler
{
    public static void GameStart(IMessage packet)
    {
        Data data = packet as Data;
        foreach(Player player in data.Player)
        {
            ObjectsManager.Instance.AddPlayer(player.Id, player);
            UnityEngine.Debug.Log(player.Id + " Inside");
        }
        foreach (Obtacle obtacle in data.Obtacle)
        {
            ObjectsManager.Instance.AddObtacle(obtacle.Id, obtacle);
            UnityEngine.Debug.Log(obtacle.Id + " Inside");
        }
    }
    public static void GameConnect(IMessage packet)
    {
        
    }
    public static void PlayerMove(IMessage packet)
    {
        Data data = packet as Data;
        Player user = data.Player[data.Player.Count - 1];

        Player player = ObjectsManager.Instance.GetPlayer(data.Id);
        // 이동 로직 구현 매차 구챠
        //player.X = user.X; player.Y = user.Y;  player.Z = user.Z;
        UnityEngine.Debug.Log(user.Id + " " + user.X + " " + user.Y + " " + user.Z);
    }

    public static void ObtacleMove(IMessage packet)
    {
        Data data = packet as Data;
        Obtacle user = data.Obtacle[data.Obtacle.Count - 1];

        Player player = ObjectsManager.Instance.GetPlayer(data.Id);
        // 이동 로직 구현 매차 구챠
        //player.X = user.X; player.Y = user.Y;  player.Z = user.Z;
        UnityEngine.Debug.Log(user.Id + " " + user.X + " " + user.Y + " " + user.Z);
    }
}