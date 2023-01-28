using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerCamera : MonoBehaviour
{

    public Transform player;
    public Vector3 offset; //카메라와 플레이어의 편차
    public float dampTrace = 20.0f; //부드러운 추적을 위한 변수

    private Vector3 targetPos;


    void LateUpdate()
    {

        targetPos = player.position + offset;
        //lerp는 선형 보간법, 벡터 a 에서 벡터 b로 변경될 때 한번에 변경되지 않고, 부드럽게 변경하기 위해서 사용 
        //마지막 매개변수가 0이면 a 반환 1이면 b 반환 0~1사이의 실수가 마지막 매개변수에 들어감
        transform.position = Vector3.Lerp(transform.position, targetPos, Time.deltaTime * dampTrace);
    }
}
