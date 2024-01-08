using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GunFollow : MonoBehaviour
{
    public RectTransform UGUICanvas;
    public Camera mainCamera;

    void Update()
    {
        Vector3 mousPos;
        RectTransformUtility.ScreenPointToWorldPointInRectangle
            (UGUICanvas, new Vector2(Input.mousePosition.x, Input.mousePosition.y), mainCamera, out mousPos);//通过mousPos传出去
        //mainCamera=Camera.main但不推荐

        //获取夹角旋转
        float z;
        if (mousPos.x > transform.position.x)
        {
            z = -Vector3.Angle(Vector3.up, mousPos - transform.position);//两线夹角
        }
        else
        {
            z = Vector3.Angle(Vector3.up, mousPos - transform.position);//两线夹角
        }
        transform.localRotation = Quaternion.Euler(0, 0, z);//四元数世界坐标
    }
}
