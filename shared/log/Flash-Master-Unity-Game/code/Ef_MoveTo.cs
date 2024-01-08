using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//金币移动到左下角
public class Ef_MoveTo : MonoBehaviour
{
    private GameObject goldCollect;
    void Start()
    {
        goldCollect = GameObject.Find("GoldCollect");//场景中找到这个金币控件
    }

    void Update()
    {
        transform.position = Vector3.MoveTowards(transform.position, goldCollect.transform.position,5 * Time.deltaTime);//移动
    }
}
