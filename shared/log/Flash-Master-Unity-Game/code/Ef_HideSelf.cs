using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//隐藏自身的特效
public class Ef_HideSelf : MonoBehaviour
{
    //隐藏的协程
    public IEnumerator HideSelf(float delay)
    {
        yield return new WaitForSeconds(delay);//delay后隐藏
        gameObject.SetActive(false);//隐藏自身
    }
    void Start()
    {
        
    }

    void Update()
    {
        
    }
}
