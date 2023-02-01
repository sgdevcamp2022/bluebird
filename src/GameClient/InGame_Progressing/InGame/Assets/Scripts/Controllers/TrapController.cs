using Google.Protobuf.Protocol;
using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.UIElements;

public class TrapController : MonoBehaviour
{
    // Start is called before the first frame update

    public float speed = 3.0f;
    Vector position = new Vector();
    public Vector PosInfo
    {
        get { return position; }
        set { position = value; }
    }

    Rigidbody rigidbody;

    void Start()
    {
        rigidbody = new Rigidbody();
    }

    // Update is called once per frame
    void Update()
    {
        UpdateController();
    }

    void UpdateController()
    {
        Vector3 pos = new Vector3(PosInfo.X, PosInfo.Y, PosInfo.Z);
        Vector3 moveDir = pos - transform.position;

        float dist = moveDir.magnitude;
        if(dist < speed * Time.deltaTime)
        {
           transform.position = pos;
        }
        else
        {
            transform.position += moveDir.normalized * speed * Time.deltaTime;
        }
    }
}
