using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Google.Protobuf.Protocol;
using static Define;


//PlayerMove 패킷 핸들러로부터 playerinfo 및 animation 정보를 최신화하여 현재 상태와 비교한다. 이를 통해, playerd의 위치 및 애니메이션을 변경한다.

public class PlayerController : MonoBehaviour
{
    public Int64 playerId { get; set; }
    [SerializeField]
    public float speed = 10.0f;
    public float jumpPower = 5.0f;

    protected Vector3 moveVec;
    protected Vector3 prevVec;



    protected Camera cam;


    protected bool pressedJump = false;
    protected bool isJumping = false;

    protected Animator animator;


    protected Rigidbody rigid;
    protected Google.Protobuf.Protocol.Animation anim;




    [SerializeField]
    protected PlayerState _state;

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
        animator = GetComponent<Animator>();
        prevVec = transform.position;
        anim = Google.Protobuf.Protocol.Animation.Idle;
        
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

    //다른 State로 넘어갈지, Idle로 남을지를 판단하는 함수
    protected virtual void UpdateIdle()
    {
        if ( (playerInfo.Position.X != prevVec.x || playerInfo.Position.Y != prevVec.y || playerInfo.Position.Z != prevVec.z) )
        {
            State = PlayerState.Moving;
            return;
        }

        switch (State)
        {
            case PlayerState.Idle:
                isJumping = false;
                animator.SetBool("MoveForward", false);
                animator.SetBool("inAir", false);
                break;
           

        }

    }
    
    protected virtual void UpdateMoving()
    {
        prevVec = transform.position;

        if (playerInfo.Position.X == prevVec.x &&  playerInfo.Position.Y == prevVec.y && playerInfo.Position.Z == prevVec.z  && !isJumping )
        {
            State = PlayerState.Idle;
            anim = Google.Protobuf.Protocol.Animation.Idle;
            animator.SetBool("MoveForward", false);
            animator.SetBool("inAir", false);
            return;
        }

        Vector3 moveVec = new Vector3(playerInfo.Position.X, playerInfo.Position.Y, playerInfo.Position.Z);
        Vector3 moveRot = new Vector3(playerInfo.Rotation.X, playerInfo.Rotation.Y, playerInfo.Rotation.Z);
        transform.position = moveVec;
        transform.rotation = Quaternion.Euler(moveRot);

        switch(anim)
        {
            case Google.Protobuf.Protocol.Animation.Idle:
                animator.SetBool("MoveForward", false);
                break;
            case Google.Protobuf.Protocol.Animation.Move:
                animator.SetBool("MoveForward", true);
                break;
            case Google.Protobuf.Protocol.Animation.JumpStart:
                animator.SetTrigger("doJump");
                break;
            case Google.Protobuf.Protocol.Animation.JumpLoop:
                animator.SetBool("inAir", true);
                break;
         
        }

       

    

    }


    protected virtual void UpdateJumping()
    {
        prevVec = transform.position;

      
        Vector3 moveVec = new Vector3(playerInfo.Position.X, playerInfo.Position.Y, playerInfo.Position.Z);
        Vector3 moveRot = new Vector3(playerInfo.Rotation.X, playerInfo.Rotation.Y, playerInfo.Rotation.Z);
        transform.position = moveVec;
        transform.rotation = Quaternion.Euler(moveRot);

        switch (anim)
        {
            case Google.Protobuf.Protocol.Animation.Idle:
                animator.SetBool("MoveForward", false);
                break;
            case Google.Protobuf.Protocol.Animation.Move:
                animator.SetBool("MoveForward", true);
                break;
            case Google.Protobuf.Protocol.Animation.JumpStart:
                animator.SetTrigger("doJump");
                break;
            case Google.Protobuf.Protocol.Animation.JumpLoop:
                animator.SetBool("inAir", true);
                break;

        }


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
            Player pkt = new Player()
            {
                Id = playerId,
                Position = playerInfo.Position,
                Rotation = playerInfo.Rotation
            };

            Managers.Network.Send(pkt, INGAME.PlayerGoal);
            Debug.Log("GameComplete Packet Sent");
        }

        if(collision.gameObject.CompareTag("Ground"))
        {
            Debug.Log("collisionGround");
            isJumping = false;
            State = PlayerState.Idle;
        }
    }

    public void SetAnim(Google.Protobuf.Protocol.Animation anim)
    {
        this.anim = anim;
    }








}
