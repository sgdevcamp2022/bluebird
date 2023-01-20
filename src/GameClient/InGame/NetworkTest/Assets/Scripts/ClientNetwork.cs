using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ClientNetwork : MonoBehaviour
{
    private Networking network;
    //byte[] bytes = new byte[1024];
   
    void Start()
    {
        network = GetComponent<Networking>();
        network.Start();

     
    }


    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            network.SendMessage();
        }
    }
}
