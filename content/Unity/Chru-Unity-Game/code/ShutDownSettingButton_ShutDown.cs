using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//设置中右上角的关闭设置按钮
public class ShutDownSettingButton_ShutDown : MonoBehaviour
{
    public void ShutDownSettingButton_ButtonDown()
    {
        if (GameManager_manager.Instance.IsSetting == true)//正常世界 打开setting
        {
            GameManager_manager.Instance.IsSetting = false;//不在设置中
            GameManager_manager.Instance.WorldTime = 1;//世界恢复
            GameManager_manager.Instance.Bg.SetActive(false);//弹走Setting
            GameManager_manager.Instance.ButtonBeWhite();//按钮恢复白色 设置全部隐藏
        }
    }
}
