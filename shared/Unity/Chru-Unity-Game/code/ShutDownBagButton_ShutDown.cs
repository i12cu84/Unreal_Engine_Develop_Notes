using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//设置中右上角的关闭设置按钮
public class ShutDownBagButton_ShutDown : MonoBehaviour
{
    public void ShutDownBagButton_ButtonDown()
    {
        if (GameManager_bag.Instance.IsSetting == true)//正常世界 打开setting
        {
            GameManager_bag.Instance.IsSetting = false;//不在设置中
            GameManager_bag.Instance.WorldTime = 1;//世界恢复
            GameManager_bag.Instance.Bag.SetActive(false);//弹走Setting
            GameManager_bag.Instance.ButtonBeWhite();//按钮恢复白色 设置全部隐藏
        }
    }
}
