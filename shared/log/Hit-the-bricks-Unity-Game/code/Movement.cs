using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//摄像机移动的脚本
public class Movement : MonoBehaviour
{
    private float moveSpeed=5.0f;
    void Start()
    {
    }

    //运动距离=速度*时间
    void Update()
    {
        float h = Input.GetAxis("Horizontal");
        float v = Input.GetAxis("Vertical");
        transform.Translate(new Vector3(h, v, 0) * Time.deltaTime * moveSpeed);

    }
}
