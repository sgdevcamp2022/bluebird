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
    Vector position = new Vector();
    Vector rotation = new Vector();
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
    void Start()
    {
        rigidbody = new Rigidbody();
        transform.position = new Vector3(position.X, position.Y, position.Z);
    }
    void Update()
    {
        UpdateController();
    }
    protected virtual void UpdateController() { }
}
