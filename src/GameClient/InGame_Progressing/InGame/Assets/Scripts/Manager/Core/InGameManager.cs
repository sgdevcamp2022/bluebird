using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using UnityEngine.UI;
public class InGameManager : MonoBehaviour
{
    public GameObject gamepanel;
    public TMP_Text racestarttxt;
    public AudioSource audioSource;

    public void GameStartTxt()
    {
        racestarttxt.text = "Game Start!";
        Invoke("InActiveGameStartTxt", 2f);
    }
    
    void InActiveGameStartTxt()
    {
        racestarttxt.enabled = false;
        gamepanel.SetActive(false);
    }
    


    
}
