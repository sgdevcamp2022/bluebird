using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEngine.UI;

public class GameManager : MonoBehaviour
{
    public Text nicknameText;

    public UserInfo player;

    public string[] args;

    private void Awake()
    {
        args = Environment.GetCommandLineArgs();
    }

    void Start()
    {
        if(args.Length == 2)
        {
            string[] arrTemp = args[1].Split(":");
            if(arrTemp.Length == 2 )
            {
                nicknameText.text = arrTemp[1];
            }
        }
        else
        {
            nicknameText.text = "Default";
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
