using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//渔网属性
public class WebAttr : MonoBehaviour
{
    public float disapperTime;//消亡时间
    public int damage;//渔网伤害
    void Start()
    {
        Destroy(gameObject, disapperTime);//指定时间后销毁自身
    }

    void Update()
    {
        
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        //碰到鱼
        if (collision.tag == "Fish")
        {
            collision.SendMessage("TakeDamage",damage);//对这个方法发消息
        }
    }
}
