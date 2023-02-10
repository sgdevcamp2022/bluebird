using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Web;
using UnityEngine;
using UnityEngine.UI;

public class GameManager : MonoBehaviour
{
    public Text nicknameText;
    public int userNo;

    public UserInfo player;

    public string[] args;

    public static GameManager gameManager;
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
                userNo = int.Parse(arrTemp[2]);
            }
        }
        else
        {
            nicknameText.text = "-1";
            userNo = -1;
        }
        //LoadUserInfo();
        //nicknameText.text = player.nickname;
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape)) 
        {
            Application.Quit();
        }
    }

    void LoadUserInfo()
    {
        string path = Path.Combine(Directory.GetCurrentDirectory(), "userInfo.json");
        string jsonData = File.ReadAllText(path);
        player = JsonUtility.FromJson<UserInfo>(jsonData);
    }
}

[System.Serializable]
public class UserInfo
{
    public int userNo;
    public string nickname;
}
