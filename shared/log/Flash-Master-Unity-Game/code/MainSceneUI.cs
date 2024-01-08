using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
//声音设置UI
public class MainSceneUI : MonoBehaviour
{
    public Toggle muteToggle;//静音按钮
    public GameObject settingPanel;//设置面板

    void Start()
    {
        muteToggle.isOn = !AudioManager.Instance.IsMute;//加载游戏后 同步UI中是否静音的勾选选项
        //if(AudioManager.Instance.IsMute)
        //{
        //    AudioManager.Instance.SwitchMuteState();//执行第三次 使得将该bug纠正
        //    //这句话有些重要
        //}
    }

    //按下MuteToggle 音量开关
    public void SwitchMute(bool isOn)//传入保存动态 而后在对应按钮内可以将函数修改成dynamic bool下的SwitchMute 
                                                                //使得每次值发生改变都将会被调用 AudioManager的41行同步
    {
        AudioManager.Instance.SwitchMuteState(isOn);//由于 按钮的事件是on value changed 所以会被调用两次造成bug
    }

    //返回 保存当前数据
    public void OnBackButtonDown()
    {
        //保存当前游戏 save game
        PlayerPrefs.SetInt("gold", GameController.Instance.gold);//金币
        PlayerPrefs.SetInt("lv", GameController.Instance.lv);//等级
        PlayerPrefs.SetFloat("scd", GameController.Instance.smallTimer);//小时间
        PlayerPrefs.SetFloat("bcd", GameController.Instance.bigTimer);//大时间
        PlayerPrefs.SetInt("exp", GameController.Instance.exp);//经验
        int temp = (AudioManager.Instance.IsMute == false) ? 0 : 1;
        PlayerPrefs.SetInt("mute", temp);//是否静音

        UnityEngine.SceneManagement.SceneManager.LoadScene(0);//回到初始场景
    }

    //显示设置面板
    public void OnSettingButtonDown()
    {
        settingPanel.SetActive(true);
    }

    //关闭设置面板
    public void OnCloseButtonDown()
    {
        settingPanel.SetActive(false);
    }

    void Update()
    {

    }
}
