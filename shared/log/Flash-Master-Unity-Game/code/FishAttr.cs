using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//记录鱼属性信息 和鱼的碰撞器销毁功能
public class FishAttr : MonoBehaviour
{
    public int hp;//血量
    public int exp;//经验
    public int gold;//金币
    public int maxNum;//最大数量
    public int maxSpeed;//最大速度
    public GameObject diePrefab;//死亡动画
    public GameObject goldPrefab;//金币

    //销毁出界鱼
    private void OnTriggerEnter2D(Collider2D collision)
    {
        //记得将要碰撞的空气墙加上Tag
        if (collision.tag == "Border")
        {
            Destroy(gameObject);//销毁鱼
        }
    }

    //鱼受到value伤害
    void TakeDamage(int value)
    {
        hp -= value;
        if (hp <= 0)
        {
            GameController.Instance.gold += gold;//获得金币
            GameController.Instance.exp += exp;//获得经验
            GameObject die=Instantiate(diePrefab);//播放死亡动画
            die.transform.SetParent(gameObject.transform.parent, false);//放在父物体之下
            die.transform.position = transform.position;//同步位移
            die.transform.rotation = transform.rotation;//同步旋转

            GameObject goldGo = Instantiate(goldPrefab);//播放金币动画
            goldGo.transform.SetParent(gameObject.transform.parent, false);//放在父物体之下
            goldGo.transform.position = transform.position;//同步位移
            goldGo.transform.rotation = transform.rotation;//同步旋转
            Destroy(gameObject);//销毁自身
        }
    }
}
