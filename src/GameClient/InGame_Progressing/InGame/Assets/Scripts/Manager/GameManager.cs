using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using UnityEngine.UI;
using UnityEngine.InputSystem;

public class GameManager : MonoBehaviour
{
    public GameObject gamepanel;
    public GameObject menupanel;


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

    public void OnGoBackLobby()
    {
        UnityEngine.SceneManagement.SceneManager.LoadScene("LobbyScene");
    }






}
