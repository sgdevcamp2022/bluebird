using Google.Protobuf.Protocol;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Cinemachine;
using static Define;

public class MyPlayerController : PlayerController
{

    CameraController cameracontroller;
    public  bool serverCommunication = false;



    bool pressedJump = false;

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
        }
        base.UpdateController();
    }

    void GetInput()
    {

        
        float h = Input.GetAxis("Horizontal");
        float v = Input.GetAxis("Vertical");

        
        pressedJump = Input.GetKeyDown(KeyCode.Space);
        moveVec = new Vector3(h, 0f, v);

        if (pressedJump && !isJumping)
        {
            State = PlayerState.Moving;
        }
    }


    protected override void UpdateIdle()
    {
        if (moveVec.x != 0 || moveVec.z != 0 || pressedJump)
        {
            State = PlayerState.Moving;
            return;
        }
    }

    //여기서 MyPlayer 이동이 이루어진다.
    protected override void UpdateMoving()
    {

        
        //내가 이동하고 좌표를 보내는 형식
       
            PlayerState prevState = State;
            prevVec = transform.position;

            if (moveVec.x == 0 && moveVec.z == 0 && !pressedJump) 
            {
                State = PlayerState.Idle;
                return;
            }

 
            Vector3 movementDirection = Quaternion.AngleAxis(cam.transform.eulerAngles.y, Vector3.up) * moveVec;
       
            movementDirection.Normalize();

            
            Debug.Log(cam.transform.eulerAngles.y);
            transform.rotation = Quaternion.Euler(0f, cam.transform.eulerAngles.y, 0f);
            
            transform.position += movementDirection * speed * Time.deltaTime;
            Jump();

            if (prevState != State || prevVec != transform.position)
            {

                Move playerMove = new Move()
                {
                    Id = playerId,
                    Position = new Vector { X = transform.position.x, Y = transform.position.y, Z = transform.position.z },
                    Rotation = new Vector { X = transform.rotation.x, Y = transform.rotation.y, Z = transform.rotation.z },

                };

                Managers.Network.Send(playerMove, INGAME.PlayerMove);

            }
        
    }

    void Jump()
    {
        if (!isJumping && pressedJump)
        {
            isJumping = true;
            pressedJump = false;
            rigid.AddForce(Vector3.up * jumpPower, ForceMode.Impulse);
            Debug.Log("Jump Success");
        }
        else
            return;
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
