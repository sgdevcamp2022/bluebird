using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor.Networking;
using UnityEngine.Networking;
using System;

public class NetworkManager : MonoBehaviour
{
    public static NetworkManager networkManager;
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

    public IEnumerator UnityWebRequestPost(bool[] selectedModes)
    {
        //string url = "https://jsonplaceholder.typicode.com/posts";
        string url = "http://127.0.0.1:8000/HTTP_Test/";
        WWWForm form = new WWWForm();
        int userID = 11;
        int id = 101;
        string body = "test body";
        string title = "test title";
        form.AddField("userID", userID);
        form.AddField("id", id);
        form.AddField("body", body);
        form.AddField("title", title);
        form.AddField("solo", Convert.ToInt32(selectedModes[0]));
        form.AddField("duo", Convert.ToInt32(selectedModes[1]));
        form.AddField("squad", Convert.ToInt32(selectedModes[2]));

        using (UnityWebRequest www = UnityWebRequest.Post(url, form))
        {
            yield return www.SendWebRequest();
            yield return new WaitForSeconds(3.0f);
            if (www.error == null)
            {
                Debug.Log(www.downloadHandler.text);
                Debug.Log("POST Result");
            }
            else
            {
                Debug.Log(www.error);
            }
            www.Dispose();
        }

    }

}
