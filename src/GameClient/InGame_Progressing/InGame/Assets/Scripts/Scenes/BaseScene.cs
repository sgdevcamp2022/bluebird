using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;


public abstract class BaseScene : MonoBehaviour
{

    //수정은 내부에서만 하고 외부에서 값을 얻어오는 형태는 밑의 코드
    public Define.Scene SceneType { get; protected set; } = Define.Scene.Unknown;

    //Start보다 먼저 실행되어, 오브젝트가 활성화 되어 있다면 스크립트가 꺼져있어도 실행. 
    //Awake는 자식들에게 상속된다.
	void Awake()
	{
        //가상 함수로 자식 Scene들에서 
		Init();
        
	}

    //가상 함수로 자식 Scene들에서 base.Init()으로 부분적으로 공통적으로 실행시켜야 하는 부분을 정의
    //EvenetSystem도 Prefab으로 만들어 생성
    protected virtual void Init()
    {
        //FindObjectOfType: 씬에 활성화된 모든 게임 오브젝트의 데이터 타입을 검색한다.
        Object obj = GameObject.FindObjectOfType(typeof(EventSystem));
        if (obj == null)
        {
            Managers.Resource.Instantiate("UI/EventSystem", null);
        }
    }


    //추상 함수로 clear의 내용은 전적으로 자식에게 맡긴다. 자식들마다 각자의 방식으로 오버라이딩
    public abstract void Clear();
}
