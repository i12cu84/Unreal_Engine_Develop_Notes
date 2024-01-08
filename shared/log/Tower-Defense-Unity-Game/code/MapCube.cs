using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
//检测mapcube上是否有炮台和建成炮台后特效的出现 更改鼠标标识
public class MapCube : MonoBehaviour
{
    [HideInInspector]//添加特性 
    public GameObject turretGo;//保存当前cube身上的炮台
    [HideInInspector]//添加特性 
    public TurrData turretData;//保存炮台的数据
    [HideInInspector]//添加特性 
    public bool isUpgraded = false;//默认炮台还未升级
    public GameObject bulidEffect;//建造成的特效
    private Renderer _renderer;//在这里声明 可以在下方不用写Getcomponent 从而节省性能

    private void Start()
    {
        _renderer = GetComponent<Renderer>();//引用Renderer
    }

    public void BuildTurret(TurrData turretData)
    {
        this.turretData = turretData;
        isUpgraded = false;//初始化没有升级
        turretGo = GameObject.Instantiate(turretData.turretPrefab, transform.position, Quaternion.identity);//实例化 且存储cube状态
        GameObject effect = GameObject.Instantiate(bulidEffect, transform.position, Quaternion.identity);//引用一次特效
        Destroy(effect, 1.5f);//延迟一秒销毁
    }

    //炮台升级
    public void UpgradeTurret()
    {
        if (isUpgraded == true) return;//已升级 因而退出
        Destroy(turretGo);
        isUpgraded = true;//初始化没有升级
        turretGo = GameObject.Instantiate(turretData.turreUpgradedPrefab, transform.position, Quaternion.identity);//实例化 且存储cube状态
        GameObject effect = GameObject.Instantiate(bulidEffect, transform.position, Quaternion.identity);//引用一次特效
        Destroy(effect, 1.5f);//延迟一秒销毁
    }

    //拆除炮台
    public void DestroyTurret()
    {
        Destroy(turretGo);
        isUpgraded = false;
        turretGo = null;
        turretData = null;
        GameObject effect = GameObject.Instantiate(bulidEffect, transform.position, Quaternion.identity);//引用一次特效
        Destroy(effect, 1.5f);//延迟一秒销毁
    }

    //鼠标移入cube变红
    private void OnMouseEnter()
    {
        if(turretGo==null && EventSystem.current.IsPointerOverGameObject()==false)//当前cube没有炮台 且鼠标没有放在ui上
        {
            _renderer.material.color = Color.red;//移入后设置红色
        }
    }

    //鼠标移出cube变白
    private void OnMouseExit()
    {
        _renderer.material.color = Color.white;//移出后恢复白色
    }

}
