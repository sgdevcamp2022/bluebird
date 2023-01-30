using System.Collections;
using System.Collections.Generic;
using UnityEngine;


/*
프리펩: 오브젝트를 애셋 파일로 만들어 두는 것을 Prefab이라고 한다. 오브젝트를 찍어내는 틀이라고 생각하면 된다.
Original Prefab: 지금 모습 그대로 바탕으로 새로운 prefab 생성, Prefab Variant: 자기 자신을 만들어 낸 프리펩을 상속받는 프리펩 생성
Instatntiate: 인스로 넘겨 받은 프리펩을 인스턴스화(실존하는 게임 오브젝트로 생성)한다. 찍어낸 게임 오브젝트 리턴

Resources.Load<GameObject>("Prefabs/Tank");
불러오려는 애셋의 타입과 애셋의 경로를 지정해주면 해당 애셋의 로컬 환경에서 찾아 Gameobject로서 불러오고 이를 리턴하는 함수이다.

여러 스크립트 내에서 Resouce.Load 함수를 사용하여 애셋을 불러오거나 아니면 직접 변수에 애셋을 할당하면, 여러 곳에서 불러오는 작업을 하므로 버그 발생 시
추적이 어렵고 수정도 어려워진다. 

 <따라서 오로지 애셋을 불러와 작업만 하는 것이 ResouceManager의 목적이다. >
 */
public class ResourceManager
{
    //Load 제네릭 사용자 지정 함수 
    //where T : Object : 부모 클래스가 Object인 타입만 받을 수 있도록 제약을 검 
    //Resouce.Load<T>(path) : Resource 폴더를 시작 위치로 한 path에 해당하는 T 타입의 애셋 파일을 불러오고 이를 리턴함
    public T Load<T>(string path) where T : Object
    {
        if (typeof(T) == typeof(GameObject))
        {
            string name = path;
            int index = name.LastIndexOf('/');
            if (index >= 0)
                name = name.Substring(index + 1);

            GameObject go = Managers.Pool.GetOriginal(name);
            if (go != null)
                return go as T;
        }

        return Resources.Load<T>(path);
    }

    //Instantiate 사용자 지정 함수 정의
    public GameObject Instantiate(string path, Transform parent = null)
    {

        //Load를 사용해 prefab에 path에 해당하는 Gameobject 타입의 애셋을 할당한다.
        GameObject original = Load<GameObject>($"Prefabs/{path}");
        if (original == null)
        {
            Debug.Log($"Failed to load prefab : {path}");
            return null;
        }
        if (original.GetComponent<Poolable>() != null)
            return Managers.Pool.Pop(original, parent).gameObject;

        //Object. 을 붙여 재귀를 막는다.
        GameObject go = Object.Instantiate(original, parent);
        go.name = original.name;
        return go;
    }

    public void Destroy(GameObject go)
    {
        if (go == null)
            return;

        Poolable poolable = go.GetComponent<Poolable>();
        if (poolable != null)
        {
            Managers.Pool.Push(poolable);
            return;
        }

        Object.Destroy(go);
    }
}
