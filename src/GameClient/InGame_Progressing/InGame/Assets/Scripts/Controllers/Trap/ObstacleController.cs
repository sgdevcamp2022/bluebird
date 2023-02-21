using Google.Protobuf.Protocol;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;
using UnityEngine.UIElements;

public class ObstacleController : MonoBehaviour
{
    Rigidbody rigidbody;

    public float speed;
    public Int32 direct;
    protected Vector3 direction;
    Vector position = new Vector();
    Vector rotation = new Vector();
    bool isRecv = false;
    public Int64 id { get; set; }
    public Vector PosInfo
    {
        get { return position; }
        set { position = value; }
    }
    public Vector RotInfo 
    { 
        get {  return rotation; }
        set { rotation = value; }
    }

    public bool PacketRecv
    {
        get { return isRecv; }
        set { isRecv = value; }
    }
    void Start()
    {
        
        rigidbody = new Rigidbody();
        transform.position = new Vector3(position.X, position.Y, position.Z);
        transform.rotation = Quaternion.Euler(rotation.X, rotation.Y, rotation.Z);

        switch (direct)
        {
            case 0:
                direction = new Vector3(1, 0, 0);
                break;
            case 1:
                direction = new Vector3(0, 1, 0);
                break;
            case 2:
                direction = new Vector3(0, 0, 1);
                break;
            default:
                direction = new Vector3(0, 0, 0);
                break;
        }

    }
    void FixedUpdate()
    {
        UpdateController();
    }

    void OnTriggerEnter(Collider other)
    {
        OnTriggerEnterController(other);
    }

    void OnTriggerExit(Collider other)
    {
        OnTriggerExitController(other);
    }

    void OnTriggerStay(Collider other)
    {
        OnTriggerStayController(other);
    }

    protected virtual void UpdateController() { }
    protected virtual void OnTriggerEnterController(Collider other) { }
    protected virtual void OnTriggerExitController(Collider other) { }
    protected virtual void OnTriggerStayController(Collider other) { }
}
