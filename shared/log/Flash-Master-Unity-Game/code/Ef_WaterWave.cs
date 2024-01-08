using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//水波纹的特效脚本 WaterWave
public class Ef_WaterWave : MonoBehaviour
{
    public Texture[] textures;//图片数组
    private Material material;//材质
    private int index = 0;

    void Start()
    {
        material = GetComponent<MeshRenderer>().material;
        InvokeRepeating("ChangeTexture",0,0.1f);//0.1秒调用一次
    }

    //改变图片的函数
    void ChangeTexture()
    {
        material.mainTexture=textures[index]; //更换材质
        index = (index + 1) % textures.Length;//避免越界
    }
}
