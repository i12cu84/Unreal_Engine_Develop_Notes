using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;
//鼠标控件对炮台的选择和建造 资金的修改
public class BuildManager : MonoBehaviour
{
    //由TurrData中写 [System.Serializable] 设置可以序列化 从而看得到public的三个式子
    public TurrData laserTurretData;//第一种炮台
    public TurrData missileTurretData;//第二种炮台
    public TurrData standerdTurretData;//第三种炮台

    //表示当前选择的炮台 要建造的炮台
    private TurrData selectedTurretData;//UI上选择炮台的属性
    private MapCube selectedMapCube;//3D中选择的其中一个炮台 表示当前选择的一个炮台(场景中的游戏物体

    public Text moneyText;//资金文本
    public Animator moneyAnimator;//资金不足闪动动画
    private int money = 1000;//初始资金

    public GameObject upgradeCanvas;//增加控件
    private Animator upgradeCanvasAnimator;//hide show的闪动动画
    public Button buttonUpgrade;//按钮
    
    //修改资金
    void ChangeMoney(int change=0)
    {
        money += change;
        moneyText.text = "￥" + money;
    }

    private void Start()
    {
        upgradeCanvasAnimator = upgradeCanvas.GetComponent<Animator>();        
    }

    private void Update()
    {
        if(Input.GetMouseButtonDown(0))//检测鼠标左键按下
        {
            if (EventSystem.current.IsPointerOverGameObject()==false)
            {
                //开发炮台的建造
                //鼠标检测点击的在MapCube层上的cube
                Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
                RaycastHit hit;
                bool isCollider = Physics.Raycast(ray, out hit, 1000, LayerMask.GetMask("MapCube"));
                if (isCollider)//点在cube上了
                {
                    MapCube mapCube = hit.collider.GetComponent<MapCube>();
                    if (selectedTurretData != null && mapCube.turretGo == null)//cube上没有炮台的时候
                    {
                        //可以创建
                        if (money >= selectedTurretData.cost)
                        {
                            //money -= selectedTurretData.cost;
                            ChangeMoney(-selectedTurretData.cost);//扣钱
                            mapCube.BuildTurret(selectedTurretData);//放相应的炮台
                        }
                        else
                        {
                            //提示钱不够
                            moneyAnimator.SetTrigger("Filcker");//触发闪动特效
                        }
                    }
                    else if(mapCube.turretGo != null)//cube上有炮台的时候
                    {
                        //升级处理
                        ShowUpgradeUI(mapCube.transform.position,mapCube.isUpgraded);//升级按钮不可交互
                        //以下同理
                        //if (mapCube.isUpgraded)
                        //{
                        //    ShowUpgradeUI(mapCube.transform.position, true);//升级按钮不可交互
                        //}
                        //else
                        //{
                        //    ShowUpgradeUI(mapCube.transform.position, false);//升级按钮可交互
                        //}
                        if(mapCube.turretGo== selectedMapCube && upgradeCanvas.activeInHierarchy)//是否同一个炮台 且 已经显示出来了
                        {
                            StartCoroutine(HideUpgradeUI());//隐藏UI StartCoroutine协程(自定义调用
                        }
                        else
                        {
                            ShowUpgradeUI(mapCube.transform.position, mapCube.isUpgraded);//显示UI
                        }
                        selectedMapCube = mapCube;//更新点击的炮台目标
                    }
                }
            }
        }
    }

    //选择指定炮台进行摆放
    public void OnLaserSelected(bool isOn)
    {
        if (isOn)
        {
            selectedTurretData = laserTurretData;
        }
    }
    public void OnMissileSelected(bool isOn)
    {
        if (isOn)
        {
            selectedTurretData = missileTurretData;
        }
    }
    public void OnStanderSelected(bool isOn)
    {
        if (isOn)
        {
            selectedTurretData = standerdTurretData;
        }
    }

    //展示升级拆卸UI
    void ShowUpgradeUI(Vector3 pos,bool isDisableUpgrade=false)//默认按钮不需要禁用
    {
        StopCoroutine("HideUpgradeUI");//暂停该方法 避免出现动画出现卡壳
        //upgradeCanvas.SetActive(false);//先隐藏初始化
        upgradeCanvas.SetActive(true);//显示
        upgradeCanvas.transform.position = pos;
        buttonUpgrade.interactable = !isDisableUpgrade;//按钮禁用
    }

    //隐藏升级拆卸UI
    IEnumerator HideUpgradeUI()
    {
        upgradeCanvasAnimator.SetTrigger("Hide");
        yield return new WaitForSeconds(0.8f);//等待0.8秒
        upgradeCanvas.SetActive(false);//隐藏显示
    }

    //升级按钮
    public void OnUpgradeButtonDown()
    {
        if (money >= selectedMapCube.turretData.costUpgraded)//
        {
            ChangeMoney(-selectedMapCube.turretData.costUpgraded);//扣所需钱财
            selectedMapCube.UpgradeTurret();//升级炮台
            StartCoroutine(HideUpgradeUI());//隐藏UI
        }
        else
        {
            //提示钱不够
            moneyAnimator.SetTrigger("Filcker");//触发闪动特效
        }
        //HideUpgradeUI();//隐藏UI
    }

    //拆除按钮
    public void OnDestroyButtonDown()
    {
        selectedMapCube.DestroyTurret();//拆炮台
        StartCoroutine(HideUpgradeUI());//隐藏UI
        //HideUpgradeUI();//隐藏UI
    }
}
