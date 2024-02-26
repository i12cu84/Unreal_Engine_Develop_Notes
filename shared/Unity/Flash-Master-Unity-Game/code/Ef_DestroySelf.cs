using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//鱼死亡动画销毁
public class Ef_DestroySelf : MonoBehaviour
{
    public float delay = 2f;//死亡销毁
    void Start()
    {
        Destroy(gameObject, delay);//指定时间后销毁自身
    }

    void Update()
    {
        
    }
}
