using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Web;
using UnityEngine;
using UnityEngine.UI;
using StackExchange.Redis;

public class LobbyGameManager : MonoBehaviour
{
    public Text nicknameText;

    public string[] args;

    public static LobbyGameManager gameManager;
    private void Awake()
    {
        gameManager = this;
        args = Environment.GetCommandLineArgs();
    }

    void Start()
    {
        if(args.Length == 2)
        {
            string[] arrTemp = args[1].Split("/");
            if(arrTemp.Length == 4 )
            {
                try
                {
                    nicknameText.text = HttpUtility.UrlDecode(arrTemp[3], Encoding.UTF8);
                }
                catch (Exception e)
                {
                    nicknameText.text = "-1";
                }
                PlayerInfo.playerInfo.userNo = int.Parse(arrTemp[2]);
                PlayerInfo.playerInfo.nickname = nicknameText.text;
            }
        }
        else
        {
            nicknameText.text = PlayerInfo.playerInfo.nickname == null ? "-1" : PlayerInfo.playerInfo.nickname;
        }
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape)) 
        {
            PlayerInfo.playerInfo.redis.HashSet(PlayerInfo.playerInfo.userNo.ToString(), "status", "LOGIN");
            Application.Quit();
        }
    }

}