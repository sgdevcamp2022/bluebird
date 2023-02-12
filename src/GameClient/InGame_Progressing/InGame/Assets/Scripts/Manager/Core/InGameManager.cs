using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using UnityEngine.UI;
public class InGameManager : MonoBehaviour
{
    public GameObject gamepanel;
    public GameObject menupanel;

    public Button continubtn;

    public TMP_Text racestarttxt;



    private void Awake()
    {
        menupanel.SetActive(false);
    }

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

    public void ActiveMenu()
    {
        menupanel.SetActive(menupanel);
        
    }

    public void OnContinue()
    {
        menupanel.SetActive(false);
    }

    
    


    
}
