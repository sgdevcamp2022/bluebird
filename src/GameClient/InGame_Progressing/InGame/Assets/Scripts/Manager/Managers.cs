using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/*
https://ansohxxn.github.io/unity%20lesson%202/ch1/
전역으로 게임 전체를 관리하는 스크립트
게임 매니저는 컴포넌트로서 어떤 오브젝트에 꼭 붙어야 할 이유가 없고, 실체가 없다.
Scene에 Empty Object를 만들어, 매니저 스크립트를 붙이고 사용하는 것을 권장한다.

게임 매니저는 게임 전반을 관리하기 때문에 딱 하나만 static으로 만들고, 여러 곳에서 이 인스턴스를 참조한다. (싱글톤)
게임 매니저 오브젝트를 여러 스크립트 컴포넌트에서 쓸 수 있도록 static으로 만들어야한다.
단 하나만 존재하는 이 게임 매니저 컴포넌트를 리턴 받을 수 있는 static 함수를 만든다.
-> 다른 곳에서 사용할 수 있도록 public

static이 붙은 것은 Unity 게임을 실행하면 바로 만들어진다.
get은 가져올 때 실행되는거니까 가져올 때 만들어진다.

<게임 전반을 관리하는 Manager>
 */

public class Managers : MonoBehaviour
{
    static Managers sInstance; // 유일성이 보장된다

    public static Managers Instance // 유일한 매니저를 갖고온다
    {
        get
        {
            Init();
            return sInstance;
        }
    } 
    #region Contents
    //MapManager _map = new MapManager();
    ObjectManager _obj = new ObjectManager();
    NetworkManager _network = new NetworkManager();

    //public static MapManager Map { get { return Instance._map; } }
    public static ObjectManager Object { get { return Instance._obj; } }
    public static NetworkManager Network
    { get
        {
            return sInstance._network;
        }
    }
    #endregion

    #region Core
    //DataManager _data = new DataManager();
    PoolManager _pool = new PoolManager();
    ResourceManager _resource = new ResourceManager();
    SceneManagerEx _scene = new SceneManagerEx();
    //SoundManager _sound = new SoundManager();
    //UIManager _ui = new UIManager();

    //public static datamanager data { get { return instance._data; } }
    public static PoolManager Pool { get { return Instance._pool; } }
    public static ResourceManager Resource { get { return Instance._resource; } }
    public static SceneManagerEx Scene { get { return Instance._scene; } }
    //public static soundmanager sound { get { return instance._sound; } }
    //public static UIManager UI { get { return Instance._ui; } }
    #endregion

    void Start()
    {
        Init();
	}

    void Update()
    {
        _network.Update();
    }

    static void Init()
    {
        if (sInstance == null)
        {
			GameObject obj = GameObject.Find("@Managers");
            if (obj == null) //Instance가 없다면 생성
            {
                obj = new GameObject { name = "@Managers" };
                obj.AddComponent<Managers>();
            }
            //다른 Scene으로 넘어가도 삭제되지 않는다.
            DontDestroyOnLoad(obj);
            sInstance = obj.GetComponent<Managers>();

            sInstance._network.Init();
            //s_instance._data.Init();
            sInstance._pool.Init();
            //s_instance._sound.Init();
        }		
	}

    public static void Clear()
    {
        //Sound.Clear();
        Scene.Clear();
        //UI.Clear();
        //Pool.Clear();
    }
}
