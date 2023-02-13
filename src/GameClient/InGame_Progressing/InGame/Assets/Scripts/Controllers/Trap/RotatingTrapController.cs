using Google.Protobuf.Protocol;
using System;
using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.UIElements;

public class RotatingTrapController : ObstacleController
{
    protected override void UpdateController()
    {
        Quaternion rot = Quaternion.Euler(RotInfo.X, RotInfo.Y, RotInfo.Z);
        Vector3 pos = new Vector3(PosInfo.X, PosInfo.Y, PosInfo.Z);
        //Vector3 moveTo = direction;


        if (PacketRecv)
        {
            transform.position = pos;
            transform.rotation = rot;
            PacketRecv = false;
        }
        else
        {
            transform.Rotate(new Vector3(0, 0, 1) * speed * Time.deltaTime / 0.05f);
        }
    }
}
