using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerManager : MonoBehaviour
{
    //属性值
    public int lifeValue = 3;//玩家生命
    public int playerScore = 0;//得分
    public bool isDead = false;//玩家是否死亡
    public bool isDefeat = false;//基地是否被破坏

    //引用
    public GameObject Born;
    public Text PlayerScoreText;
    public Text PlayerLifeValueText;
    public GameObject isDefeatUI;

    //单例
    private static PlayerManager instance;//ctrl+r+e ↓

    public static PlayerManager Instance { 
        get => instance; 
        set => instance = value; 
    }

    private void Awake()
    {
        Instance = this;
    }

    private void Update()
    {
        isDefeatUI.SetActive(false);//显示gameover
        if (isDefeat)
        {
            isDefeatUI.SetActive(true);//显示gameover
            return;
        }
        if (isDead)
        {
            Recover();
        }
        //将text组件的数字进行更改
        PlayerScoreText.text = playerScore.ToString();//需要修改类型
        PlayerLifeValueText.text = lifeValue.ToString();
    }

    //玩家复活方法
    private void Recover()
    {
        if (lifeValue <= 0)
        {
            //游戏失败
            isDefeat = true;
        }
        else
        {
            lifeValue--;
            GameObject go = Instantiate(Born, new Vector3(-2, -8, 0), Quaternion.identity);//在出生点复活
            go.GetComponent<Born>().createPlayer = true;//设定成玩家
            isDead = false;
        }
    }
}
