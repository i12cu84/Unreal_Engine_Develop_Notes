using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//子弹的方法
public class bullet : MonoBehaviour
{
    public float moveSpeed=10;//子弹移动速度
    public bool isPlayerBullet=false;//是否为玩家子弹

    void Start()
    {
        
    }

    void Update()
    {
        transform.Translate(transform.up * moveSpeed * Time.deltaTime, Space.World);//在世界坐标轴下作移动
    }

    //触发器Trigger的检测
    private void OnTriggerEnter2D(Collider2D collision)//注意有2D
    {
        switch (collision.tag)
        {
            case "Tank":
                if(!isPlayerBullet)//不是玩家子弹碰到玩家
                {
                    collision.SendMessage("Die");//打中坦克 触发死亡
                    Destroy(gameObject);
                }
                break;
            case "Heart":
                collision.SendMessage("Die");//触发die方法
                Destroy(gameObject);
                break;
            case "Enemy":
                if(isPlayerBullet)
                {
                    collision.SendMessage("Die");//敌人调用die方法
                    Destroy(gameObject);
                }
                break;
            case "Wall":
                Destroy(collision.gameObject);//销毁墙
                Destroy(gameObject);//销毁自身
                break;
            case "Barrier":
                Destroy(gameObject); 
                break;
            default:
                break;
        }
    }
}
