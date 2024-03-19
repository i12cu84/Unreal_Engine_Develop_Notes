using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Gedeyes_Follow : MonoBehaviour
{
    public Transform Hero;//玩家主角色位置
    private Vector3 offset;//当前位置偏移
    void Start()
    {
        offset = transform.position - Hero.position;
    }

    void Update()
    {
        transform.position = offset + Hero.position;//位置
    }
}
