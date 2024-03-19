using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//用于右上角Setting按钮触发打开Setting的控件脚本
public class EscSetting_ShowSetting : MonoBehaviour
{
    //按下按钮呼出Setting
    public void EscSetting_ButtonDown()
    {
        if (GameManager_manager.Instance.IsSetting == false)//正常世界 打开setting
        {
            GameManager_manager.Instance.IsSetting = true;//在设置中
            GameManager_manager.Instance.WorldTime = 0;//世界暂停
            GameManager_manager.Instance.Bg.SetActive(true);//弹出Setting
            GameManager_manager.Instance.TitleText.text = "Setting";//显示标题为设置
        }
    }
}
