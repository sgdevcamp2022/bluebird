using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//using UnityEditor.Networking;
using UnityEngine.Networking;
using System;

public class LobbyNetworkManager : MonoBehaviour
{
    public static LobbyNetworkManager networkManager;
    private void Awake()
    {
        networkManager = this;
    }
    public IEnumerator UnityWebRequestGet()
    {
        //string jobId = "41f1cdc2ff58bb5fdc287be0db2a8df3";
        //string jobGrowId = "df3870efe8e8754011cd12fa03cd275f";
        //string url = $"https://api.neople.co.kr/df/skills/{jobId}?jobGrowId={jobGrowId}&apikey=Of8CEcOZmRObP2oMVbnaDF9KMJSjZd5z";
        string url = "http://127.0.0.1:8000/HTTP_Test/";
        UnityWebRequest www = UnityWebRequest.Get(url);

        yield return www.SendWebRequest();

        if (www.error == null)
        {
            Debug.Log(www.downloadHandler.text);
        }
        else
        {
            Debug.Log("ERROR");
        }
    }

    public IEnumerator MatchInitPost(Action<bool> callback)
    {
        //string url = "https://jsonplaceholder.typicode.com/posts";
        string url = "http://127.0.0.1:8000/lobby/start/";
        
        //Debug.Log("UserNo: " + userNo);
        WWWForm form = new WWWForm();

        int userNo = LobbyGameManager.gameManager.userNo;
        int modsSum = PanelManager.panelManager.modsSum;

        Debug.Log("Mods: " + modsSum);

        form.AddField("userNo", userNo);
        form.AddField("level", modsSum);
        
        using (UnityWebRequest www = UnityWebRequest.Post(url, form))
        {
            yield return www.SendWebRequest();
            yield return new WaitForSeconds(1.0f);
            if (www.error == null)
            {
                MatchStart matchStart = JsonUtility.FromJson<MatchStart>(www.downloadHandler.text);
                Debug.Log(www.downloadHandler.text);
                callback(matchStart.result);
            }
            else
            {
                Debug.Log(www.error);
                callback(false);
            }
            www.Dispose();
        }

    }

    public IEnumerator MatchStartPost(bool isCancel, Action<int> callback)
    {
        if(isCancel)
        {
            callback(-2);
            yield break;
        }
        //string url = "https://jsonplaceholder.typicode.com/posts";
        string url = "http://127.0.0.1:8000/lobby/check/";

        //Debug.Log("UserNo: " + userNo);
        WWWForm form = new WWWForm();

        int userNo = LobbyGameManager.gameManager.userNo;

        form.AddField("userNo", userNo);

        using (UnityWebRequest www = UnityWebRequest.Post(url, form))
        {
            yield return www.SendWebRequest();
            yield return new WaitForSeconds(1.0f);
            if (www.error == null)
            {
                MatchCheck matchCheck = JsonUtility.FromJson<MatchCheck>(www.downloadHandler.text);
                Debug.Log(www.downloadHandler.text);
                if(matchCheck.result == -1)
                {
                    Debug.Log("매치가 아직 시작되지 않음");
                    callback(-1);
                }
                else
                {
                    Debug.Log("매칭 완료");
                    callback(matchCheck.result);
                }
            }
            else
            {
                Debug.Log(www.error);
                Debug.Log("매치가 아직 시작되지 않음");
                callback(-1);
            }
            www.Dispose();
        }

    }

    public IEnumerator MatchCancelPost(Action<bool> callback)
    {
        //string url = "https://jsonplaceholder.typicode.com/posts";
        string url = "http://127.0.0.1:8000/lobby/cancel";

        //Debug.Log("UserNo: " + userNo);
        WWWForm form = new WWWForm();

        int userNo = LobbyGameManager.gameManager.userNo;

        form.AddField("userNo", userNo);

        using (UnityWebRequest www = UnityWebRequest.Post(url, form))
        {
            yield return www.SendWebRequest();
            yield return new WaitForSeconds(1.0f);
            if (www.error == null)
            {
                MatchCancel matchCancel = JsonUtility.FromJson<MatchCancel>(www.downloadHandler.text);
                Debug.Log(www.downloadHandler.text);
                callback(matchCancel.result);
            }
            else
            {
                Debug.Log(www.error);
                callback(false);
            }
            www.Dispose();
        }

    }
}

[System.Serializable]
class MatchStart
{
    public bool result;
}

[System.Serializable]
class MatchCheck
{
    public int result;
}

[System.Serializable]
class MatchCancel
{
    public bool result;
}