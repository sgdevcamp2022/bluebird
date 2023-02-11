using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AudioManager : MonoBehaviour
{
    public AudioSource musicSource;
    
    public void SetMusicVolume(float volume)
    {
        musicSource.volume = volume;
    }
}
