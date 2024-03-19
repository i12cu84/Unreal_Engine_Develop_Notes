using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;//加载场景
//对第0场景UI中 开始游戏和继续游戏两个按钮进行设定的脚本
public class ScriptsHolder_manager : MonoBehaviour
{
    public void NewGame()
    {
        PlayerPrefs.DeleteAll();//删除所有数据
        SceneManager.LoadScene(1);//传送到1场景
    }

    public void OldGame()
    {
        SceneManager.LoadScene(1);//传送到1场景
    }

    void Start()
    {
        
    }

    void Update()
    {
        
    }
}
