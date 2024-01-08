using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//豆子的脚本
public class Pacdot : MonoBehaviour
{
    public bool isSuperPacdot = false;//是否为超级豆子

    //当物体上有 bos collider 并且勾选is trigger时 在有东西进入触发器范围后调用
    public void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.name == "Pacman")//触发触发器是否为吃豆人
        {
            GameManager.Instance.nowEat++;
            if (isSuperPacdot)//吃了超级豆子
            {
                GameManager.Instance.score += 2;//吃超级豆子
                GameManager.Instance.OnEatPacdot(gameObject);//将游戏物体自身传过去
                GameManager.Instance.OnEatSuperPacdot();//
                Destroy(gameObject);//销毁豆子
                //告诉GameManager我是超级豆子而且还被吃了
                //让吃豆人边成超级吃豆人 可以吃鬼
            }
            else
            {
                Destroy(gameObject);//销毁豆子
                GameManager.Instance.score += 1;//吃普通豆子
            }
        }
    }
}
