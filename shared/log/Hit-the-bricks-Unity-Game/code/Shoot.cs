using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//发射小球
public class Shoot : MonoBehaviour
{
    public GameObject bulletPrefab;
    void Start()
    {
        //根据Prefab创建实例 = 实例化Prefab
        //GameObject.Instantiate(bulletPrefab,transform.position,transform.rotation);//instantiate实例化参数( Prefab , 位置 , 旋转角度)
    }

    void Update()
    {
        //Input输入
        if (Input.GetMouseButtonDown(0))//鼠标左键
        {
            GameObject bullet= GameObject.Instantiate(bulletPrefab, transform.position, transform.rotation);//instantiate实例化参数( Prefab , 位置 , 旋转角度)
            Rigidbody rd=bullet.GetComponent<Rigidbody>();//获取刚体组件
            //rd.AddForce(Vector3.forward*100);//100牛顿力量
            rd.velocity = Vector3.forward * 30;//10米每秒
        }
    }
}
