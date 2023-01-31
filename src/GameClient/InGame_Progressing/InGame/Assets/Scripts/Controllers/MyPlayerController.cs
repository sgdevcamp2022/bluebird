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

   

    protected override void GetInput()
    {
        h = Input.GetAxis("Horizontal");
        v = Input.GetAxis("Vertical");

        if (h == 0.0 && v == 0.0)
            _state = PlayerState.Idle;

        else
            _state = PlayerState.Moving;
    }


}
