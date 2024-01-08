using System.Collections;//就能用协程
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;//SceneManager.LoadScene() 动画加载

//随机 让不同的鬼拿到不同的随机路径 (该模式目前禁用
public class GameManager : MonoBehaviour
{

    public bool isSuperPacman = false;//是否吃了超级豆子进入超级状态
    public List<int> usingIndex = new List<int>();//数索引值
    public List<int> rawIndex = new List<int> { 0 };//原始数值 鬼的序号
    public List<GameObject> pacdotGos = new List<GameObject>();

    private static GameManager _instance;
    public static GameManager Instance
    {
        get
        {
            return _instance;
        }
    }

    public GameObject Pacman;//吃豆人名字
    public GameObject Blinky;//鬼名字
    public GameObject startPanel;//开始
    public GameObject gamePanel;//退出
    public GameObject startCountDownPrefab;//321go 开始
    public GameObject gameoverPrefab;//game over游戏结束
    public GameObject winPrefab;//win胜利
    public AudioClip startClip;//开始音乐

    public Text remainText;//记录豆子总数
    public Text nowText;//记录吃了多少豆子
    public Text scoreText;//记录分数

    public int pacdotNum = 0;//豆子总数
    public int nowEat = 0;//吃了多少豆子
    public int score = 0;//得分

    private void Awake()
    {
        _instance = this;
        //setting->Player-> Logos->Logos 并且写以下语句
        Screen.SetResolution(1024, 768, false);//写死分辨率
        int tempCount = rawIndex.Count;//因为会减少 而循环要不能变化
        for (int i = 0; i < tempCount; i++)
        {
            int tempIndex = Random.Range(0, rawIndex.Count);//随机
            usingIndex.Add(rawIndex[tempIndex]);//添加到索引
            rawIndex.RemoveAt(tempIndex);//移除到数值
        }
        foreach (Transform t in GameObject.Find("Maze").transform)//在地图中
        {
            pacdotGos.Add(t.gameObject);//拿到手
        }
        pacdotNum = GameObject.Find("Maze").transform.childCount;//记录地图中所有豆子的总数
    }

    //
    private void Start()
    {
        SetGameState(false);//游戏所有主体暂停运动
    }

    //
    private void Update()
    {
        if (nowEat == pacdotNum && Pacman.GetComponent<PacmanMove>().enabled!=false)//吃完所有豆子 且脚本没有被暂停
        {
            gamePanel.SetActive(false);
            Instantiate(winPrefab);//win动画
            StopAllCoroutines();//将调用的协程都取消了保护进程
            SetGameState(false);//游戏状态暂停 此时再次调用该if 将不会重复调用
        }
        if (nowEat == pacdotNum)
        {
            if (Input.anyKey)//由于游戏结束 按下任意键则重新开始游戏
            {
                SceneManager.LoadScene(0);//加载0号场景
            }
        }
        if(gamePanel.activeInHierarchy)//如果UI显示 需要实时更新
        {
            remainText.text = "Remain:\n\n" + (pacdotNum - nowEat);
            nowText.text = "Eaten:\n\n" + nowEat;
            scoreText.text = "Score:\n\n" + score;
        }
    }

    //
    public void OnStartButton()
    {
        StartCoroutine(PlayStartCountDown());
        AudioSource.PlayClipAtPoint(startClip, new Vector3(0,0,-5));//播放歌曲 放播放点声源坐标
        //SetGameState(true);//游戏所有主体暂停运动
        //Invoke("CreateSuperRacdot", 10f);//延迟调用
        startPanel.SetActive(false);
        GetComponent<AudioSource>().Play();//播放bgm
    }

    //
    public void OnExitButton()
    {
        Application.Quit();//退出
    }

    //
    IEnumerator PlayStartCountDown()//协同类型
    {
        GameObject go = Instantiate(startCountDownPrefab);
        yield return new WaitForSeconds(3f);//3秒后运作
        Destroy(go);//销毁动画
        SetGameState(true);//全局开始运动
        Invoke("CreateSuperRacdot", 10f);//延迟调用
        gamePanel.SetActive(true);
    }

    //被吃的豆子从表中移除
    public void OnEatPacdot(GameObject go)
    {
        nowEat++;//吃了一个豆子记录下
        score ++;//吃个豆子+100分 不知道为什么不会调用
        pacdotGos.Remove(go);//超级豆子被吃后 也要记得把超级豆子原豆子在列表中移除
    }

    //生成下一个超级豆子
    public void OnEatSuperPacdot()
    {
        score += 2;//吃个超级豆子+200分 不知道为什么不会调用
        Invoke("CreateSuperRacdot", 10);//延迟调用 没有吃豆子10秒后 其中一个豆子变成超级豆子
        isSuperPacman = true;//变成超级吃豆人
        FreezeEnemy();//吃超级豆子后 鬼被冻结
        //RecoveryEnemy为void时 使用以下句
        //Invoke("RecoveryEnemy", 5);//延迟调用 恢复普通吃豆人
        StartCoroutine(RecoveryEnemy());//协程 延时调用 上句同理
        //超级吃豆人五秒后恢复吃豆人
    }

    //恢复成吃豆人
    IEnumerator RecoveryEnemy()//协程变量用法
    {
        yield return new WaitForSeconds(5f);//等三秒
        DisFreezeEnemy();
        isSuperPacman = false;//变成吃豆人
    }

    //生成超级豆子
    private void CreateSuperRacdot()
    {
        if (pacdotGos.Count < 15)
        {
            //由于吃豆人可能会吃掉了本来要变成超级豆子的普通豆子之后 产生了bug
            return;//豆子太少了就不生成超级豆子了
        }
        int tempIndex = Random.Range(0, pacdotGos.Count);

        //个人添加的修复bug的方式 :如果突然被吃豆人吃了 则取消此次强化 
        if (pacdotGos[tempIndex] == null) return;

        pacdotGos[tempIndex].transform.localScale = new Vector3(3, 3, 3);//放大三倍
        pacdotGos[tempIndex].GetComponent<Pacdot>().isSuperPacdot = true;//变成超级豆子
    }

    //敌人被冻结
    private void FreezeEnemy()
    {
        //鬼禁止移动
        Blinky.GetComponent<GhostMove>().enabled = false;//禁用鬼移动脚本

        //鬼颜色被改变 
        Blinky.GetComponent<SpriteRenderer>().color = new Color(0.7f, 0.7f, 0.7f, 0.7f);//变透明
    }

    //敌人被解冻
    private void DisFreezeEnemy()
    {
        //鬼禁止移动
        Blinky.GetComponent<GhostMove>().enabled = true;//启用鬼移动脚本

        //鬼颜色被改变 
        Blinky.GetComponent<SpriteRenderer>().color = new Color(1f, 1f, 1f, 1f);//恢复
    }

    //游戏刚开始之前 禁用一切
    private void SetGameState(bool state)
    {
        //禁止一切移动
        Blinky.GetComponent<GhostMove>().enabled = state;//鬼禁用移动脚本
        Pacman.GetComponent<PacmanMove>().enabled = state;//吃豆人禁用移动
    }
}
