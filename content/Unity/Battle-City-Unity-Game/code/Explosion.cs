using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//爆炸的方法
public class Explosion : MonoBehaviour
{
    void Start()
    {
        Destroy(gameObject, 0.167f);
    }

    void Update()
    {
        
    }
}
