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
    public float speed = 5.0f;
    protected float h, v;

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
            UpdateMove();
        }
    }


    void Start()
    {
        Init();
    }

    void Update()
    {
        GetInput();
        UpdateMove();
    }



    protected virtual void Init()
    {
        _rigidbody = GetComponent<Rigidbody>();
    }

    /*
	protected virtual void UpdateController()
	{
		switch (State)
		{
			case PlayerState.Idle:
				GetDirInput();
				break;
			case PlayerState.Moving:
				GetDirInput();
				break;
		}
		
		UpdateController();
	}
    */

    // 키보드 입력
    void GetInput()
    {
        h = Input.GetAxis("Horizontal");
        v = Input.GetAxis("Vertical");

        if (h == 0.0 && v == 0.0)
            _state = PlayerState.Idle;

        else
            _state = PlayerState.Moving;
            
    }

    void UpdateMove()
    {
        if (_state == PlayerState.Moving)
        {
            //벡터 값을 1로 보정해줌 
            moveVec = new Vector3(h, 0, v).normalized;

            transform.position += moveVec * speed * Time.deltaTime;

            transform.LookAt(transform.position + moveVec);
        }
    
       
    }

  


}
