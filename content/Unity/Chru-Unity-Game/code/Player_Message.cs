using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
//个人信息
public class Player_Message : MonoBehaviour
{
    public int Gold = 5000;//默认金币
    public int Diamond = 100;//默认钻石
    public int kiki = 0;//点券
    public int Sex = 0;//0女1男

    public int Physics = 10;//物理攻击
    public int Chemistry = 10;//法术攻击
    public int Physics_Defense = 10;//物理防御
    public int Chemistry_Defense = 0;//法术防御
    public int Tired_Defense = 20;//体力耐性
    public int Attribute = 0;//属性攻击 0普通攻击
    public int Weapon = 0;//武器 0拳头

    public float Hp = 100;//默认生命
    public float Hp_Max = 100;//最大值生命
    public float Hp_Percent = 1f;//血量百分比
    public float Hp_Recover = 1f;//血量恢复速度
    public float Mp = 100;//默认体力
    public float Mp_Max = 100;//最大体力
    public float Mp_Percent = 1f;//体力百分比
    public float Mp_Recover = 1f;//血量恢复速度
    public float Safe = 5;//默认护盾
    public float Safe_Max = 5;//最大值护盾

    public float Move_Speed = 5f;//移动速度
    public float Move_ShiftSpeed = 3f;//冲刺速度
    public float Move_Shiftcd = 1f;//冲刺cd
    public float JumpGravity = 150f;//跳跃力度
    public float Move_Jumpcd = 1f;//跳跃cd
    public float Attack_Range = 1.5f;//攻击范围
    public float Physics_Tetanic = 1f;//物理攻击僵直
    public float Chemistry_Tetanic = 1f;//法术攻击僵直
    public float Tetanic = 0.5f;//受击僵直

    public Text Hp_Percent_Text;//血量百分比显示
    public Text Mp_Percent_Text;//体力百分比显示
    public Slider Hp_Percent_Slider;//血量横条显示
    public Slider Mp_Percent_Slider;//血量横条显示

    //实例化
    private static Player_Message _instance;
    public static Player_Message Instance//其他方法以该方法调用获值
    {
        get
        {
            return _instance;
        }
    }

    void Awake()
    {
        _instance = this;//获得自身 初始化时便返回自身
        Init_Player();//属性初始化
    }

    //初始化玩家特性
    void Init_Player()
    {
        Hp = Hp_Max;//最大值生命
        Safe = Safe_Max;//最大值护盾
    }

    void Start()
    {

    }

    void FixedUpdate()
    {
        HpMp_Recover();//血量体力状态恢复
    }

    //血量体力状态恢复
    void HpMp_Recover()
    {
        //血量恢复
        if (Hp < Hp_Max)//低于血量最大值
        {
            Hp += 0.01f * Hp_Recover;//恢复血量
        }

        //体力恢复
        if (Mp < Mp_Max)//低于体力最大值
        {
            Mp += 0.01f * Mp_Recover;//恢复体力
        }
    }

    void Update()
    {
        HpMp_Effect();
    }

    //HpMp 血量体力变更和特效
    void HpMp_Effect()
    {
        //Hp的恢复和特效
        Hp_Percent = Hp / Hp_Max;//血量百分比
        if (Hp_Percent >= 1)//血量满值
        {
            Hp_Percent = 1;
            Hp = Hp_Max;
        }
        else
        {
            Hp_Percent_Text.text = (int)(Hp_Percent * 100 + 0.5) + "%";
        }
        Hp_Percent_Slider.value = Hp_Percent;//血量条增减
        if (Hp_Percent <= 0.5)
        {
            Hp_Percent_Text.color = Color.red;//低于50血 危机
        }
        else
        {
            Hp_Percent_Text.color = Color.white;//高于50血 正常
        }

        //Mp的恢复和特效
        Mp_Percent = Mp / Mp_Max;//体力百分比
        if (Mp_Percent >= 1)//体力满值
        {
            Mp_Percent = 1;
            Mp = Mp_Max;
        }
        else
        {
            Mp_Percent_Text.text = (int)(Mp_Percent * 100 + 0.5) + "%";
        }
        Mp_Percent_Slider.value = Mp_Percent;//体力条增减
        if (Mp_Percent <= 0.5)
        {
            Mp_Percent_Text.color = Color.blue;//低于50体 危即
        }
        else
        {
            Mp_Percent_Text.color = Color.white;//高于50体 正常
        }
    }

    //受到伤害 生命受损
    public bool Hurt_Player(float Physics_damage, float Chemistry_damage)
    {
        float damage = (Physics_damage) * //计算受护甲减免后实际伤害
            (1 - Physics_Defense / 100) + Chemistry_damage * (1 - Chemistry_Defense / 100);
        //护盾判定
        if (Safe > damage)//如果有盾
        {
            Safe = Safe - damage;
            damage = 0;
        }
        else
        {
            damage = damage - Safe;
            Safe = 0;
        }
        Hp = Hp - damage;
        if (Hp >= 0) return true;//生还
        else return false;//阵亡
    }

    //跳跃冲刺 体力受损
    public bool Tired_Player(float damage)
    {
        damage = damage * (1 - Tired_Defense / 100);//计算耐性削减后的实际体力消耗
        if (Mp >= damage)
        {
            Mp = Mp - damage;
            return true;//减体
        }
        else return false;//疲劳
    }

}
