using Google.Protobuf.Protocol;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Cinemachine;
using static Define;


//제자리 점프할때 Idle인데 isJumping은 True인 상태가 지속되서 상대방에게 안보인다.
public class MyPlayerController : PlayerController
{

    CameraController cameracontroller;
    public  bool serverCommunication = false;



    

    protected override void Init()
    {
        
        base.Init();
     
    }

    protected override void UpdateController()
    {
        switch (State)
        {
            case PlayerState.Idle:
                GetInput();
                break;
            case PlayerState.Moving:
                GetInput();
                break;
            case PlayerState.Jumping:
                GetInput();
                break;

        }
        base.UpdateController();
    }

    void GetInput()
    {

        
        float h = Input.GetAxis("Horizontal");
        float v = Input.GetAxis("Vertical");

        
        pressedJump = Input.GetKeyDown(KeyCode.Space);
        moveVec = new Vector3(h, 0f, v).normalized;

        if (pressedJump && !isJumping)
        {
            State = PlayerState.Jumping; 
        }

        Debug.Log("State : " + State + " isJumping: " + isJumping);

    }

    //Idle로 계속 남을지, 다른 상태로 넘어갈지를 판단.
    protected override void UpdateIdle()
    {
        if (transform.position.y < -1)
        {
            transform.position = new Vector3(0.1f, 0.2f, 29f);
            transform.rotation = Quaternion.Euler(0, 180f, 0f);
        }

        if (moveVec.x != 0 || moveVec.z != 0 )
        {
            State = PlayerState.Moving;
            return;
        }

        State = PlayerState.Idle;

        UpdateAnimation();


       


    }

    //플레이어가 먼저 이동하고 좌표를 보냄, 플레이어의 지상에서의 움직임을 제어한다.
    protected override void UpdateMoving()
    {

           if(transform.position.y <-1)
            {
                transform.position = new Vector3(0.1f, 0.2f, 29f);
                transform.rotation = Quaternion.Euler(0, 180f, 0f);
            }
     
            prevVec = transform.position;
     
 
            Vector3 movementDirection = Quaternion.AngleAxis(cam.transform.eulerAngles.y, Vector3.up) * moveVec;
       
             movementDirection.Normalize();
         
           
        
            transform.rotation = Quaternion.Euler(0f, cam.transform.eulerAngles.y, 0f);
            transform.position += movementDirection * speed * Time.deltaTime;



            UpdateAnimation();



            if (moveVec != Vector3.zero )
            {
   
                animator.SetBool("MoveForward", true);

            }

            if (prevVec != transform.position)
            {

               
                    Move playerMove = new Move()
                    {
                        Id = playerId,
                        Position = new Vector { X = transform.position.x, Y = transform.position.y, Z = transform.position.z },
                        Rotation = new Vector { X = transform.eulerAngles.x, Y = transform.eulerAngles.y, Z = transform.eulerAngles.z },
                        Anim = Google.Protobuf.Protocol.Animation.Move,

                    };

                    Managers.Network.Send(playerMove, INGAME.PlayerMove);
 
           }

            else if (prevVec == transform.position)
            {
                
                State = PlayerState.Idle;
             
            }
        
    }


    //점프를 해서 착지할때까지 계속해서 패킷을 보내줘야한다.

    protected override void UpdateJumping()
    {
       

        Vector3 movementDirection = Quaternion.AngleAxis(cam.transform.eulerAngles.y, Vector3.up) * moveVec;

        movementDirection.Normalize();

        transform.rotation = Quaternion.Euler(0f, cam.transform.eulerAngles.y, 0f);

        //바닥에 착지해있는 상태라면 점프 수행
        if (!isJumping)
        {
            Jump();
            isJumping = true;
        }

        //아직까지 공중에 떠있다면 계속해서 패킷 전송, 공중에서도 움직일 수 있도록 Moving으로 변경
        if (isJumping)
        {
            UpdateAnimation();
        }

        Move playerMove = new Move()
        {
             Id = playerId,
             Position = new Vector { X = transform.position.x, Y = transform.position.y, Z = transform.position.z },
             Rotation = new Vector { X = transform.eulerAngles.x, Y = transform.eulerAngles.y, Z = transform.eulerAngles.z },
             Anim = Google.Protobuf.Protocol.Animation.JumpLoop,     
        };


        Managers.Network.Send(playerMove, INGAME.PlayerMove);


    }

    void Jump()
    {
        if (!isJumping )
        {
            rigid.AddForce(Vector3.up * jumpPower, ForceMode.Impulse);
            animator.SetTrigger("doJump");
           
        }
        else
            return;
    }

    void UpdateAnimation()
    {
        switch (State)
        {
            case PlayerState.Idle:
                isJumping = false;
                animator.SetBool("MoveForward", false);
                animator.SetBool("inAir", false);
                break;
            case PlayerState.Moving:
                isJumping = false;
                animator.SetBool("MoveForward", true);
                animator.SetBool("inAir", false);
                break;
            case PlayerState.Jumping:
                isJumping = true;
                animator.SetBool("MoveForward", false);
                animator.SetBool("inAir", true);
                break;

        }
    }

  


}


/*
 //서버가 좌표를 보내주면 이동하는 형식
        if (serverCommunication)
        {
            PlayerState prevState = State;
            prevVec = transform.position;


        
            //moveVec = transform.position + (moveVec * speed * Time.deltaTime);




            if (prevState != State || prevVec != moveVec)
            {

                Move playerMove = new Move()
                {
                    Id = playerId,
                    Position = new Vector { X = moveVec.x, Y = moveVec.y, Z = moveVec.z },
                    Rotation = new Vector { X = moveVec.x, Y = moveVec.y, Z = moveVec.z },
                };

                Managers.Network.Send(playerMove, INGAME.PlayerMove);

            }

            if (playerInfo.Position.X == prevVec.x && playerInfo.Position.Z == prevVec.z)
            {
                State = PlayerState.Idle;
                return;
            }
            else
            {
                State = PlayerState.Moving;
                moveVec = new Vector3(playerInfo.Position.X, playerInfo.Position.Y, playerInfo.Position.Z);
                transform.position = moveVec;

                Debug.Log("Player:UpdateMoving : moveVec    " + moveVec + "State :" + State);
            }
        }
        */
