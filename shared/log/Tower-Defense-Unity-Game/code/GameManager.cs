using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
//游戏胜利或失败的方法
public class GameManager : MonoBehaviour
{
    public GameObject endUI;//结束UI
    public Text endMessage;//结束文本显示
    public static GameManager Instance;//这个其实没看懂
    private EnemySpawner enemySpawner;//世界中停止生成enemy
    void Awake()
    {
        Instance = this;
        enemySpawner = GetComponent<EnemySpawner>();
    }

    //胜利调用结局
    public void Win()
    {
        endUI.SetActive(true);
        endMessage.text = "胜 利";
    }

    //失败调用结局
    public void Failed()
    {
        enemySpawner.Stop();
        endUI.SetActive(true);
        endMessage.text = "失 败";
    }

    //重玩 加载当前场景
    public void OnbuttonRetry()
    {
        //引入UnityEngine.SceneManagement命名空间后
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);//加载当前场景
    }

    //菜单 menu
    public void OnButtonMenu()
    {
        SceneManager.LoadScene(0);//返回菜单

    }
}
