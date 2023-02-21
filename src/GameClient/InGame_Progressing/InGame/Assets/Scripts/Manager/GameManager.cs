using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using UnityEngine.UI;
using UnityEngine.InputSystem;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    public GameObject gamepanel;
    public GameObject menupanel;
    public GameObject completepanel;


    public Text racestarttxt;
    public Text goalnumtxt;
    public TMP_Text userId;
    public TMP_Text userposition;



    private void Awake()
    {
        menupanel.SetActive(false);
    }

    public void GameStartTxt()
    {
        racestarttxt.text = "레이스 시작!";
        Invoke("InActiveGameStartTxt", 2f);
    }

    void InActiveGameStartTxt()
    {
        racestarttxt.enabled = false;
        //gamepanel.SetActive(false);
    }

    public void ActiveMenu()
    {
        menupanel.SetActive(menupanel);

    }

    public void OnContinue()
    {
        menupanel.SetActive(false);
    }

    public void OnGoBackLobby()
    {
        UnityEngine.SceneManagement.SceneManager.LoadScene("LobbyScene");
    }

    public void SetGoalNumText(string txt)
    {
        goalnumtxt.text = txt;
    }

    public void SetUserId(string txt)
    {
        userId.text += txt;
    }

    public void SetUserPosition(string txt)
    {
        userposition.text = txt;
    }
    






}
