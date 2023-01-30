using System.Collections;
using System.Collections.Generic;
using UnityEngine;


/*
 한번 Instatntiate 한 클론 오브젝트를 계속 재활용하는 형태
  Pool에 미리 생성할 오브젝트를 모아놓고 비활성화한다.
  사용할 때만 활성화하여 Pool에서 빼내온다. (pop)
  사용하지 않을때만 마치 파괴되는 것처럼 비활성화만 하고 다시 Pool에 넣는다. (push)
     
<Pooling 할 Prefab에 붙여서 사용>


 */
public class Poolable : MonoBehaviour
{
	public bool IsUsing;
}