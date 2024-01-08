using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//音效管理
public class AudioManager : MonoBehaviour
{
    private static AudioManager _instance;//注意要写静态 才能被其他cs引用
    public static AudioManager Instance//注意要写静态 才能被其他cs引用
    {
        get
        {
            return _instance;
        }
    }

    private bool isMute = false;//是否禁音
    public bool IsMute//只让访问不让修改
    {
        get
        {
            return isMute;
        }
    }

    public AudioSource bgmAudioSource;//声音组件
    public AudioClip seaWaveClip;//浪花转场
    public AudioClip goldClip;//得钱
    public AudioClip rewardClip;//奖励
    public AudioClip fireClip;//开火
    public AudioClip changeClip;//换炮
    public AudioClip lvUpClip;//升级

    void Awake()
    {
        _instance = this;
        isMute = (PlayerPrefs.GetInt("mute", 0) == 0) ? false : true;//默认不禁音 返回0
        Domute();//对bgm操作
    }

    //声音取反 bgm静音
    public void SwitchMuteState(bool isOn)//MainSceneUI的23行同步传入
    {
        isMute = !isOn;
        Domute();//对bugm操作
    }


    //对bugm操作
    void Domute()
    {
        if (isMute)
        {
            bgmAudioSource.Pause();//暂停bgm
        }
        else
        {
            bgmAudioSource.Play();//播放bgm
        }
    }

    //播放clip
    public void PlayEffectSound(AudioClip clip)
    {
        if (!isMute)//如果非禁音则播放
        {
            AudioSource.PlayClipAtPoint(clip, new Vector3(0, 0, -5));
        }
    }
    void Start()
    {

    }

    void Update()
    {

    }
}
