using Google.Protobuf.Protocol;
using System;
using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.UIElements;

public class TrapController : ObstacleController
{
    // Start is called before the first frame update
    // Update is called once per frame
    bool goPositive = true;
    Vector3 prevPos;
    protected override void UpdateController()
    {
        Vector3 pos = new Vector3(PosInfo.X, PosInfo.Y, PosInfo.Z);

        if (PacketRecv)
        {
            if (prevPos.x < pos.x || prevPos.y < pos.y || prevPos.z < pos.z)
            {
                goPositive = false;
            }
            else
            {
                goPositive = true;
            }
            transform.position = pos;
            PacketRecv = false;
        }
        else
        {
            if (goPositive)
            {
                transform.position += direction * speed * Time.deltaTime;
            }
            else
            {
                transform.position -= direction * speed * Time.deltaTime;
            }
        }

        prevPos = pos;
    }
}
