using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
//enemy行为
public class Enemy : MonoBehaviour
{
    public float speed = 10;//敌人速度
    public float hp = 150;//默认血量
    private float totalHp;//血量上限
    public GameObject explosionEffect;//敌人爆炸引入
    private Slider hpSlider;//血条组件
    private Transform[] positions;//敌人移动路线点数
    private int index = 0;//索引数组
    void Start()
    {
        positions = Waypoint.positions;//移动路线点
        totalHp = hp;//血量上限
        hpSlider = GetComponentInChildren<Slider>();
    }

    void Update()
    {
        Move();
    }

    void Move()
    {
        if (index > positions.Length - 1) return;//如果下标越界则退出
        transform.Translate((positions[index].position - transform.position).normalized*Time.deltaTime*speed);//末-初 向量
        if (Vector3.Distance(positions[index].position, transform.position) < 0.2f)//如果到达目标位置 
        {
            index++;//移动下一个位置
        }
        if (index > positions.Length - 1)
        {
            ReachDestination();
        }
    }

    //到达终点 销毁敌人 游戏结束弹出界面
    void ReachDestination()
    {
        GameManager.Instance.Failed();
        GameObject.Destroy(this.gameObject);
    }

    //销毁后场内敌人数-1
    void OnDestroy()
    {
        EnemySpawner.CountEnemyAlive--;
    }

    public void TakeDamage(float damage)
    {
        if (hp <= 0) return;
        hp -= damage;//扣血
        hpSlider.value = (float)hp / totalHp;
        if (hp <= 0)
        {
            Die();
        }
    }

    void Die()
    {
        GameObject effect= GameObject.Instantiate(explosionEffect, transform.position, transform.rotation);//触发死亡特效
        Destroy(effect, 1.5f);//销毁死亡特效
        Destroy(this.gameObject);//销毁物体
    }
}
