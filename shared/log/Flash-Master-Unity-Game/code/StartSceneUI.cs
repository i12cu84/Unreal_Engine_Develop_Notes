using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;//加载场景
//初始场景开始游戏
public class StartSceneUI : MonoBehaviour
{
    public void NewGame()
    {
        //PlayerPrefs.DeleteAll();//删除所有数据 //但是会出现 连声音禁用的数据也被删除的bug
        PlayerPrefs.DeleteKey("gold");
        PlayerPrefs.DeleteKey("lv");
        PlayerPrefs.DeleteKey("exp");
        PlayerPrefs.DeleteKey("scd");
        PlayerPrefs.DeleteKey("bcd");
        SceneManager.LoadScene(1);//开始原来的场景
    }

    public void OldGame()
    {
        SceneManager.LoadScene(1);//开始原来的场景
    }

    void Start()
    {
        
    }

    void Update()
    {
        
    }
}
