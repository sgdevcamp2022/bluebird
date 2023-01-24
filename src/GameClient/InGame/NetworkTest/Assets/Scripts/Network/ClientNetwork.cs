using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ClientNetwork : MonoBehaviour
{
    public float speed, jumpPower;
    float h, v;

    bool jDown;
    bool isJump = false;

    private Networking network;

    Vector3 moveVec;
    Rigidbody rigid;
    //byte[] bytes = new byte[1024];

    void Awake()
    {
        rigid = GetComponent<Rigidbody>();
    }


    void Start()
    {
        network = GetComponent<Networking>();
        network.Start();
        network.SendMessage();


    }


    void Update()
    {

        GetInput();
        Move();
        Turn();
        Jump();

        if (Input.GetKeyDown(KeyCode.E))
            network.SendMessage();
    }

    void GetInput()
    {
        h = Input.GetAxisRaw("Horizontal");
        v = Input.GetAxisRaw("Vertical");
        jDown = Input.GetButtonDown("Jump");

    }

    void Move()
    {
        //∫§≈Õ ∞™¿ª 1∑Œ ∫∏¡§«ÿ¡‹ 
        moveVec = new Vector3(h, 0, v).normalized;

        transform.position += moveVec * speed * Time.deltaTime;
        network.SendPlayerMessage(this.gameObject);
    }

    void Turn()
    {
        transform.LookAt(transform.position + moveVec);
    }

    void Jump()
    {
        if (jDown && !isJump)
        {
            rigid.AddForce(Vector3.up * jumpPower, ForceMode.Impulse);
            isJump = true;
        }
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.tag == "Floor")
        {
            isJump = false;
        }
    }

}
