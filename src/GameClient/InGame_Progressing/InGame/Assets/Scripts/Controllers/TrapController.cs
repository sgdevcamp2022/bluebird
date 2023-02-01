using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TrapController : MonoBehaviour
{
    // Start is called before the first frame update

    public float maxX = 5.0f;
    public float minX = -5.0f;
    float moveX = 0.0f;

    bool trapCon = false;

    public float speed = 3.0f;
    Rigidbody rigidbody;


    void Start()
    {
        rigidbody = new Rigidbody();
    }

    // Update is called once per frame
    void Update()
    {
        if (moveX >= maxX)
            trapCon = true;
        else if (moveX <= minX)
            trapCon = false;

        if (trapCon)
            moveX -= 0.1f;
        else
            moveX += 0.1f;
        
        transform.position += new Vector3(moveX,0,0) * speed * Time.deltaTime;     
    }
}
