using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Google.Protobuf.Protocol;
using static Define;

public class PlayerController : MonoBehaviour
{
    public Int64 id { get; set; }
    [SerializeField]
    public float speed = 10.0f;
    protected float h, v;

    protected Vector3 prevVec;
    protected Vector3 moveVec;
    protected Animator _animator;
    protected Rigidbody _rigidbody;
    

    [SerializeField]
    protected PlayerState _state = PlayerState.Idle;

    public virtual PlayerState State
    {
        get { return _state; }
        set
        {
            if (_state == value)
                return;

            _state = value;
            //UpdateAnimation();
        }
    }

    Player _playerInfo = new Player();

    public Player playerInfo
    {
        get { return _playerInfo; }
        set
        {
            if (_playerInfo.Equals(value))
                return;

            _playerInfo = value;
            //UpdateMove();
        }
    }


    void Start()
    {
        Init();
    }

    void Update()
    {

        UpdateVec();
        UpdateMove();

    }



    protected virtual void Init()
    {
        _rigidbody = GetComponent<Rigidbody>();
        prevVec = transform.position;
    }

    

    // 키보드 입력
    protected virtual void GetInput()
    {

      
    }

    protected Vector3 UpdateVec()
    {

        if (_state == PlayerState.Moving)
        {
            //벡터 값을 1로 보정해줌 
            //moveVec = new Vector3(h, 0, v).normalized;

            moveVec = new Vector3(h, 0, v);
            moveVec = transform.position * speed * Time.deltaTime; 

            Debug.Log("UpdateVec : moveVec : " + moveVec);

            //transform.position += moveVec * speed * Time.deltaTime;
            //transform.LookAt(transform.position + moveVec);

            return moveVec;
        }
        else
            return prevVec;       
    }

    protected void UpdateMove()
    {
        Debug.Log("UpdateMove");
        transform.position += moveVec * speed * Time.deltaTime;
        transform.LookAt(transform.position + moveVec);

        prevVec = transform.position;
    }




}
