using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using static Define;

public class MyPlayerController : PlayerController
{


    void Start()
    {
        base.Init();

    }

    void Update()
    {
        GetInput();
        UpdateVec();
        UpdateMove();
    }

    protected override void GetInput()
    {
        h = Input.GetAxis("Horizontal");
        v = Input.GetAxis("Vertical");

        //Debug.Log("h" + h + "v" + v);
        if (h == 0.0 && v == 0.0)
        {
            _state = PlayerState.Idle;
            moveVec = new Vector3(0, 0, 0);
        }

        else
            _state = PlayerState.Moving;
    }


}
