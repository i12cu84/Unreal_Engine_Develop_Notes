using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//用于右上角Bag按钮触发打开Bag的控件脚本
public class BagButton_ShowBag : MonoBehaviour
{
    //按下按钮呼出Bag
    public void BagButton_ButtonDown()
    {
        if (GameManager_bag.Instance.IsSetting == false)//正常世界 打开setting
        {
            GameManager_bag.Instance.IsSetting = true;//在设置中
            GameManager_bag.Instance.WorldTime = 0;//世界暂停
            GameManager_bag.Instance.Bag.SetActive(true);//弹出Setting
            GameManager_bag.Instance.TitleText.text = "Bag";//显示标题为设置
        }
    }
}
