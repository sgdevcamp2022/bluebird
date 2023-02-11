using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LobbyInfo : MonoBehaviour
{
    public int userNo;
    public int room;

    public static LobbyInfo lobbyInfo;
    private void Awake()
    {
        lobbyInfo = this;
    }

    // Start is called before the first frame update
    void Start()
    {
        DontDestroyOnLoad(this.gameObject);
    }
}
