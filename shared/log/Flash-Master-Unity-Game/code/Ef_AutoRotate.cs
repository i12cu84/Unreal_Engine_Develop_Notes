using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//旋转鱼
public class Ef_AutoRotate : MonoBehaviour
{
    public float speed = 10f;

    void Start()
    {
        
    }

    void Update()
    {
        transform.Rotate(Vector3.forward, speed * Time.deltaTime);
    }
}
