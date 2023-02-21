using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

//이미 SceneManager가 유니티엔진에 있기에 EX를 붙여서 구분, 여러 Scene들을 한꺼번에 관리하는 역할을 한다.
public class SceneManagerEx
{
    //GameScene 등이 할당될 것이다. BaseScene의 자식들이기 때문에
    public BaseScene CurrentScene { get { return GameObject.FindObjectOfType<BaseScene>(); } }

	public void LoadScene(Define.Scene type)
    {
        Managers.Clear();

        SceneManager.LoadScene(GetSceneName(type));
    }

    string GetSceneName(Define.Scene type)
    {
        string name = System.Enum.GetName(typeof(Define.Scene), type);
        return name;
    }

    public void Clear()
    {
        CurrentScene.Clear();
    }
}
