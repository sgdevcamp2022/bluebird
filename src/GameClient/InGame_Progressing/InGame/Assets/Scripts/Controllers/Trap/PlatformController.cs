using Google.Protobuf.Protocol;
using System;
using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.UIElements;

public class PlatformController : MonoBehaviour
{
    public float speed = 2.0f;
    Rigidbody rigidbody;

    float max = 5.0f;
    float min = -5.0f;
    float moveX = 0.0f;
    bool translateMode = true;

    void Start()
    {
        rigidbody = new Rigidbody();
 

    }

    void Update()
    {
        if(moveX >= max)
        {
            translateMode = false;
        }
        else if(moveX <= min)
        {
            translateMode = true;
        }

        if(translateMode)
        {
            moveX += 0.1f;
        }
        else
        {
            moveX -= 0.1f;
        }

        transform.position += new Vector3(moveX, 0, 0) * speed * Time.deltaTime;
    }

   
}
