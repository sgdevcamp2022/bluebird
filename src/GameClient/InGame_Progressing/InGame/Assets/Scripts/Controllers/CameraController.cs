using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Cinemachine;

public class CameraController : MonoBehaviour
{

    static CameraController cameraInstance;

    public static CameraController Instance
    {
        get
        {
            //여기서 init 한번 해줘야할듯??
            Init();
            return cameraInstance;
        }
    }

    private CinemachineFreeLook cinemachineFreeLook;


    private Transform targetTransform;

    //게임이 시작되기 전에 호출한다.
    private void Awake()
    {
        Camera.main.gameObject.TryGetComponent<CinemachineBrain>(out var brain);

        if(brain == null)
        {
            brain = Camera.main.gameObject.AddComponent<CinemachineBrain>();
        }



        cinemachineFreeLook = gameObject.AddComponent<CinemachineFreeLook>();


        cinemachineFreeLook.m_XAxis.m_InvertInput = false;
        cinemachineFreeLook.m_Orbits[0].m_Height = 8;
        cinemachineFreeLook.m_Orbits[0].m_Radius = 15;
        cinemachineFreeLook.m_Orbits[1].m_Height = 8;
        cinemachineFreeLook.m_Orbits[1].m_Radius = 15;
        cinemachineFreeLook.m_Orbits[2].m_Height = 8;
        cinemachineFreeLook.m_Orbits[2].m_Radius = 15;







        //transposer.m_FollowOffset = new Vector3(0f, 5f, -12f);
        // pov.m_VerticalAxis.Value = 18.0f;
        //  pov.m_VerticalAxis.m_InputAxisName = null;








    }

    static void Init()
    {
        if(cameraInstance == null)
        {
            GameObject obj = GameObject.Find("Virtual Camera");

            cameraInstance = obj.GetComponent<CameraController>();
        }

       
    }




    public void SetFollowTarget(GameObject Target)
    {
        if (Target == null)
        {
           
            return;
        }
        Debug.Log("SetFollowTarget: " + Target);
        targetTransform = Target.transform;
        cinemachineFreeLook.Follow = targetTransform;
        cinemachineFreeLook.LookAt = targetTransform;

    }

  
}
