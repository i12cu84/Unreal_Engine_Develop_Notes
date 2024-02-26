using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//金币碰撞后销毁脚本
public class GoldCollect : MonoBehaviour
{
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.tag == "Gold")
        {
            AudioManager.Instance.PlayEffectSound(AudioManager.Instance.goldClip);//播放获得金币声音
            //销毁金币
            //Destroy(gameObject);//这个写错了 销毁的是金币触发器
            Destroy(collision.gameObject);//销毁碰撞到的东西
        }
    }
    void Start()
    {
        
    }

    void Update()
    {
        
    }
}
