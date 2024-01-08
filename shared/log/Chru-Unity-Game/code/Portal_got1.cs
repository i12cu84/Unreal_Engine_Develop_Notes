﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;//加载场景
//第一个传送门的传出脚本 
public class Portal_got1 : MonoBehaviour
{
    //如果触发触发器
    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Player")
        {
            //触发传送阵效果 传送到第一个目标点
            SceneManager.LoadScene(2);//开始原来的场景
        }
    }
    void Start()
    {
        
    }

    void Update()
    {
        
    }
}
