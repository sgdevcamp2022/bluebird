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
    protected Vector3 serverVec;

    protected Animator _animator;
    protected Rigidbody _rigidbody;

    bool playerInfoUpdated = false;

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
            //serverVec = new Vector3(value.Position.X,value.Position.Y,value.Position.Z);
            //State = PlayerState.Moving;
            

            Debug.Log("PlayerInfo " +  this.id + "     ServerVec:     " + this.serverVec + " State : " + State );
        }
    }


    void Start()
    {
        Init();
    }

    void Update()
    {

        UpdateController();

    }



    protected virtual void Init()
    {
        _rigidbody = GetComponent<Rigidbody>();
        prevVec = transform.position;
    }

   

   

    protected virtual void UpdateController()
    {
       
        switch (State)
        {
            case PlayerState.Idle:
                UpdateIdle();
                break;
            case PlayerState.Moving:
                UpdateMoving();
                break;
        }

    }

    protected virtual void UpdateIdle()
    {
        if (playerInfo.Position.X != 0 || playerInfo.Position.Z != 0)
        {
            
            State = PlayerState.Moving;
            return;
        }

    }
    
    protected virtual void UpdateMoving()
    {

        if (playerInfo.Position.X == 0 && playerInfo.Position.Z == 0)
        {
            State = PlayerState.Idle;
            return;
        }

        Vector3 moveVec = new Vector3(playerInfo.Position.X, playerInfo.Position.Y, playerInfo.Position.Z);
        transform.position += moveVec * speed * Time.deltaTime;

        Debug.Log("Player:UpdateMoving : moveVec    " + moveVec + "State :" + State );



        /*
        if (playerInfoUpdated)
        {
          
            serverVec = new Vector3(playerInfo.Position.X, playerInfo.Position.Y, playerInfo.Position.Z);
            transform.position = serverVec;
           //playerInfoUpdated = false;
           // State = PlayerState.Idle;
        }
        else
        {
            //Debug.Log("PlayerInfoUpdate");
            if (h == 0 && v == 0)
            {
                State = PlayerState.Idle;
                return;
            }
            Vector3 moveVec = new Vector3(h, 0, v);
            transform.position += moveVec * speed * Time.deltaTime;
        }

    */

    }



    protected virtual void MoveToNextPos()
    {
       
    }

    public void playerInfoUpdate ()
    {
        //State = PlayerState.Moving;
        playerInfoUpdated = true;
    }





}
