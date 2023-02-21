using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameScene : BaseScene
{

    static GameScene gamescene;

    private bool canStartGame = false;

   
    protected override void Init() //상속 받은 Awake() 안에서 실행됨. GameScene 초기화
    {

        base.Init();

        SceneType = Define.Scene.Game;

        //Managers.Map.LoadMap(1);

        Screen.SetResolution(1920, 1080, true);


        

    }

    public override void Clear()
    {
        
    }

    public void SetStartGame()
    {
        canStartGame = true;
    }

    public bool CheckStartGame()
    {
        if (canStartGame)
            return true;
        else
            return false;
    }
}
