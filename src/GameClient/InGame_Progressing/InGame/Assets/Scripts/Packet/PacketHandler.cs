using Google.Protobuf;
using Google.Protobuf.Protocol;
//using UnityEditor.Timeline.Actions;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PacketHandler
{

    public static  Google.Protobuf.Protocol.Vector spawnPoint = new Vector { X = 0.1f, Y = 0.2f, Z = 29f };
    public static Google.Protobuf.Protocol.Vector spawnRotation = new Vector { X = 0f, Y = 180f, Z = 0f };

    static bool firstStage = true;
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
    //MyPlayer랑 Player 다시 생성해야한다.
    // 첫 스테이지에서만 실행된다
    public static void GameStart(IMessage packet)
    {

            UnityEngine.Debug.Log("Game Start...");
            StartData data = packet as StartData;


        if (!firstStage)
        {

                foreach (Player player in data.Player)
                {
                    if (player.Id == Managers.Object.myPlayerId)
                    {
                        UnityEngine.Debug.Log("MyPlayer created" + Managers.Object.myPlayerId);
                        Managers.Object.AddMyPlayer(player.Id, player);
                    }
                    else
                    {

                        Managers.Object.AddPlayer(player.Id, player);
                        UnityEngine.Debug.Log(player.Id + " Inside");
                    }
                }
            
        }
        else
        {
            foreach (Player player in data.Player)
            {
                //Player Spawn
                if (Managers.Object.MyPlayer.playerId == player.Id)
                    continue;
                Managers.Object.AddPlayer(player.Id, player);
                UnityEngine.Debug.Log(player.Id + " Inside");
            }
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
        StartData data = packet as StartData;
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

    //Connect 단계에서는 Random 한 위치에 생성 후, Start 단계에서 스폰위치에 스폰
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
        ConnectData data = packet as ConnectData;
        if (data.Id == -1)
            UnityEngine.Debug.Log("Id Error");
        else if(data.Room == -1)
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

        if (data.Success)
        {
            firstStage = false;
            Managers.Object.ClearPlaayers();
            Managers.Object.ClearObstacle();
            Managers.Object.ClearShape();

            UnityEngine.Debug.Log("Scene Moved");
            SceneManager.LoadScene("Stage2");

        }
        else
        {
            firstStage = true;
            Managers.Object.ClearPlaayers();
            Managers.Object.ClearObstacle();
            Managers.Object.ClearShape();
            SceneManager.LoadScene("LobbyScene");
        }

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
        GameObject go = Managers.Object.GetPlayer(data.Id);

        if (go == null)
            return;

        PlayerController pc = go.GetComponent<PlayerController>();
        if (pc == null)
            return;

        if (data.Success)
        {
          
        }
        else
        {
            
        }


    }



}