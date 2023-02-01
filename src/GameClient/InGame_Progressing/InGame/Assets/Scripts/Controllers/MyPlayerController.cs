using Google.Protobuf.Protocol;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using static Define;

public class MyPlayerController : PlayerController
{


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



    protected override void UpdateMoving()
    {
        PlayerState prevState = State;
        Vector3 prevVec = transform.position;

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

            Managers.Network.Send(playerMove,INGAME.PlayerMove);

        }

    }


}
