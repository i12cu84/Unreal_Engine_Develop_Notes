using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
//菜单开始和退出

public class GameMenu : MonoBehaviour
{
    public void OnStartGame()
    {
        SceneManager.LoadScene(1);
    }

    public void OnExitGame()
    {
        //定义宏
#if UNITY_EDITOR//编辑器下运行时
        UnityEditor.EditorApplication.isPlaying = false;//判断当前是否运行 false->停止运行
#else
        Application.Quit();
#endif 
        //Application.Quit();
    }
}
