using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//炮台存储数据
[System.Serializable]//设置可以序列化 从而看得到public的三个式子
public class TurrData
{
    public GameObject turretPrefab;//炮台组件
    public int cost;//炮台费用
    public GameObject turreUpgradedPrefab;//炮台升级后的组件
    public int costUpgraded;//炮台升级费用
    public TurretType type;//炮台类型
}
public enum TurretType
{
    LaserTurret,//第一种炮台
    MissleTurret,//第二种炮台
    StandardTurret//第三种炮台
}