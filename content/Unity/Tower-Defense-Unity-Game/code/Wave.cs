using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//保存每一波敌人生成所需要的属性
[System.Serializable]//需要添加序列化特性 这个不太懂
//EnemySpwner.cs中的public Wave[] waves; 需要有[System.Serializable]才会显示
public class Wave//因此不需要继承monobehavior
{
    public GameObject EnemyPrefab;
    public int count;
    public float rate;

}
