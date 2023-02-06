using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Google.Protobuf.Protocol;
using static Define;

public class PlayerController : MonoBehaviour
{
    public Int64 playerId { get; set; }
    [SerializeField]
    public float speed = 10.0f;
    public float jumpPower = 5.0f;

    protected Vector3 moveVec;
    protected Vector3 prevVec;

    protected bool isJumping = false;

    protected Animator _animator;
    // protected Rigidbody _rigidbody;

    protected Rigidbody rigid;

    


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

        rigid = GetComponent<Rigidbody>();
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
        if (playerInfo.Position.X != 0 || playerInfo.Position.Y != 0 || playerInfo.Position.Z != 0)
        {
            
            State = PlayerState.Moving;
            return;
        }

    }
    
    protected virtual void UpdateMoving()
    {
        prevVec = transform.position;

        if (playerInfo.Position.X == prevVec.x &&  playerInfo.Position.Y == prevVec.y && playerInfo.Position.Z == prevVec.z)
        {
            State = PlayerState.Idle;
            return;
        }

        Vector3 moveVec = new Vector3(playerInfo.Position.X, playerInfo.Position.Y, playerInfo.Position.Z);
        transform.position = moveVec;

        Debug.Log("Player:UpdateMoving : moveVec    " + moveVec + "State :" + State );

    }



    protected virtual void MoveToNextPos()
    {
       
    }

    protected void HideCursor()
    {
        Cursor.lockState = CursorLockMode.Locked;
    }

    protected void OnCollisionEnter(Collision collision)
    {
        if(collision.gameObject.CompareTag("Victory Ground"))
        {
            isJumping = false;
            Data pkt = new Data()
            {
                Id = playerId,
                MapLevel = 2,
                MatchRoom = 0,
                Player = { new Player
                {   Position = new Vector { X = transform.position.x, Y = transform.position.y, Z = transform.position.z },
                    Rotation = new Vector { X = transform.rotation.x, Y = transform.rotation.y, Z = transform.rotation.z }}
                },
            };

            Managers.Network.Send(pkt, INGAME.GameComplte);
            Debug.Log("GameComplete Packet Sent");
        }

        if(collision.gameObject.CompareTag("Ground"))
        {
            isJumping = false;
        }
    }








}
