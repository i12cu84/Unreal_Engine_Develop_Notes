using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//camera移动
public class ViewController : MonoBehaviour
{
    public float speed = 25;
    public float mouseSpeed = 3;
    void Start()
    {
        
    }

    void Update()
    {
        //世界坐标平移
        float h = Input.GetAxis("Horizontal");
        float v = Input.GetAxis("Vertical");
        float mouse = Input.GetAxis("Mouse ScrollWheel");
        transform.Translate(new Vector3(h, mouse*mouseSpeed, v)*Time.deltaTime*speed,Space.World);


    }
}
