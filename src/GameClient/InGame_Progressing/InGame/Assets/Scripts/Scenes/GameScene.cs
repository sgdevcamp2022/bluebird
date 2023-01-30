using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameScene : BaseScene
{
    protected override void Init() //상속 받은 Awake() 안에서 실행됨. GameScene 초기화
    {
        base.Init();

        SceneType = Define.Scene.Game;

        //Managers.Map.LoadMap(1);

        Screen.SetResolution(640, 480, false);




       
    }

    public override void Clear()
    {
        
    }
}
