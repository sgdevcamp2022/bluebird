using Google.Protobuf.Protocol;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using static Define;

public class MyPlayerController : PlayerController
{

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
        }
        base.UpdateController();
    }

    void GetInput()
    {
        h = Input.GetAxis("Horizontal");
        v = Input.GetAxis("Vertical");

    }


    protected override void UpdateIdle()
    {
        if (h != 0 || v != 0)
        {

            State = PlayerState.Moving;
            return;
        }
    }

    //여기서 MyPlayer 이동이 이루어진다.
    protected override void UpdateMoving()
    {

        //서버가 좌표를 보내주면 이동하는 형식
        if (serverCommunication)
        {
            PlayerState prevState = State;
            prevVec = transform.position;


            Vector3 moveVec = new Vector3(h, 0, v);
            moveVec = transform.position + (moveVec * speed * Time.deltaTime);
            //moveVec += transform.position * speed * Time.deltaTime;



            if (prevState != State || prevVec != moveVec)
            {

                Move playerMove = new Move()
                {
                    Id = id,
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
        //내가 이동하고 좌표를 보내는 형식
        else
        {
            PlayerState prevState = State;
            prevVec = transform.position;

            if (h == 0 && v == 0)
            {
                State = PlayerState.Idle;
                return;
            }

            Vector3 moveVec = new Vector3(h, 0, v);
            transform.position += moveVec * speed * Time.deltaTime;

            if (prevState != State || prevVec != transform.position)
            {

                Move playerMove = new Move()
                {
                    Id = id,
                    Position = new Vector { X = transform.position.x, Y = transform.position.y, Z = transform.position.z },
                    Rotation = new Vector { X = transform.rotation.x, Y = transform.rotation.y, Z = transform.rotation.z },

                };

                Managers.Network.Send(playerMove, INGAME.PlayerMove);

            }
        }
    }
}