using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//浪花特效
public class Ef_SeaWave : MonoBehaviour
{
    private Vector3 temp;//起始镜像位置
    void Start()
    {
        temp = -transform.position;
    }

    void Update()
    {
        transform.position = Vector3.MoveTowards(transform.position, temp,5*Time.deltaTime);//右往左跑过去
    }
}
