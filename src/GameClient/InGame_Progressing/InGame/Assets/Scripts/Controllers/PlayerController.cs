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



    protected Camera cam;

    //canJump를 위한 변수
    protected bool pressedJump = false;
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
        cam = Camera.main.gameObject.GetComponent<Camera>();
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
            case PlayerState.Jumping:
                UpdateJumping();
                break;
          
        
        }

    }

    protected virtual void UpdateIdle()
    {
        if (playerInfo.Position.X != prevVec.x || playerInfo.Position.Y != prevVec.y || playerInfo.Position.Z != prevVec.z )
        {
            
            State = PlayerState.Moving;
            return;
        }

    }
    
    protected virtual void UpdateMoving()
    {
        prevVec = transform.position;

        if (playerInfo.Position.X == prevVec.x &&  playerInfo.Position.Y == prevVec.y && playerInfo.Position.Z == prevVec.z  && !isJumping)
        {
            State = PlayerState.Idle;
            return;
        }

        Vector3 moveVec = new Vector3(playerInfo.Position.X, playerInfo.Position.Y, playerInfo.Position.Z);
        Vector3 moveRot = new Vector3(playerInfo.Rotation.X, playerInfo.Rotation.Y, playerInfo.Rotation.Z);
        transform.position = moveVec;
        transform.rotation = Quaternion.Euler(moveRot);

       

    

    }


    protected virtual void UpdateJumping()
    {
        prevVec = transform.position;

      
        Vector3 moveVec = new Vector3(playerInfo.Position.X, playerInfo.Position.Y, playerInfo.Position.Z);
        Vector3 moveRot = new Vector3(playerInfo.Rotation.X, playerInfo.Rotation.Y, playerInfo.Rotation.Z);
        transform.position = moveVec;
        transform.rotation = Quaternion.Euler(moveRot);





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
            GameCompleteData pkt = new GameCompleteData()
            {
                Id = playerId,
                Success = true,
            };

            Managers.Network.Send(pkt, INGAME.GameComplte);
            Debug.Log("GameComplete Packet Sent");
        }

        if(collision.gameObject.CompareTag("Ground"))
        {
            isJumping = false;
            State = PlayerState.Idle;

        }
    }








}
