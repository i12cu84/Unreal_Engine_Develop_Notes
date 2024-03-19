using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//地图实例化
public class MapCreation : MonoBehaviour
{
    //用来装饰初始化地图所需物体的数组
    //0.Heart 1.Wall 2.Barrier 3.Born 4.River 5.Grass 6.AirBarrier
    public GameObject[] item;

    //已经有东西的位置列表
    private List<Vector3> itemPositionList = new List<Vector3>();

    private void Awake()
    {
        //实例化老家
        CreateItem(item[0],new Vector3(0, -8, 0), Quaternion.identity);
        //用墙围起老家
        CreateItem(item[1],new Vector3(-1, -8, 0), Quaternion.identity);
        CreateItem(item[1],new Vector3(1, -8, 0), Quaternion.identity);
        CreateItem(item[1],new Vector3(-1, -7, 0), Quaternion.identity);
        CreateItem(item[1],new Vector3(0, -7, 0), Quaternion.identity);
        CreateItem(item[1],new Vector3(1, -7, 0), Quaternion.identity);

        //实例化空气墙
        for (int i = -11; i < 12; i++)
        {
            CreateItem(item[6], new Vector3(i, 9, 0), Quaternion.identity);
        }
        for (int i = -11; i < 12; i++)
        {
            CreateItem(item[6], new Vector3(i, -9, 0), Quaternion.identity);
        }
        for (int i = -8; i < 9; i++)
        {
            CreateItem(item[6], new Vector3(11, i, 0), Quaternion.identity);
        }
        for (int i = -8; i < 9; i++)
        {
            CreateItem(item[6], new Vector3(-11, i, 0), Quaternion.identity);
        }

        //初始化敌人 玩家
        GameObject go = Instantiate(item[3], new Vector3(-2, -8, 0), Quaternion.identity);
        go.GetComponent<Born>().createPlayer = true;//产生玩家 create打勾

        //先产生敌人三个
        CreateItem(item[3], new Vector3(-10, 8, 0), Quaternion.identity);
        CreateItem(item[3], new Vector3(0, 8, 0), Quaternion.identity);
        CreateItem(item[3], new Vector3(10, 8, 0), Quaternion.identity);

        InvokeRepeating("CreateEnemy", 4, 5);//对CreateEnemy方法 第一次产生4秒之后 每隔五秒调用一次方法

        //实例化地图
        for (int i = 0; i < 60; i++)//墙
        {
            CreateItem(item[1], CreateRandowPosition(), Quaternion.identity);
        }
        for (int i = 0; i < 20; i++)//障碍
        {
            CreateItem(item[2], CreateRandowPosition(), Quaternion.identity);
        }
        for (int i = 0; i < 20; i++)//草
        {
            CreateItem(item[4], CreateRandowPosition(), Quaternion.identity);
        }
        for (int i = 0; i < 20; i++)//河流
        {
            CreateItem(item[5], CreateRandowPosition(), Quaternion.identity);
        }
    }

    //原先使用 Instantiate函数 而封装的CreateItem函数是将构建的物品在Hierarchy的MapCreation附件下构建
    private void CreateItem(GameObject createGameObject,Vector3 createPosition,Quaternion createRotation)
    {
        GameObject itemGo = Instantiate(createGameObject, createPosition,createRotation);
        itemGo.transform.SetParent(gameObject.transform);
        itemPositionList.Add(createPosition);
    }

    //产生随机位置的方法
    private Vector3 CreateRandowPosition()
    {
        //不生成x=-10\10的两列 y=-8\8两行
        while (true)
        {
            Vector3 createPosition = new Vector3(Random.Range(-9, 10), Random.Range(-7, 8), 0);
            if (!HasThePosition(createPosition))
            {
                return createPosition;
            }
        }
    }

    //用来判断这个列表中是否有这个位置
    private bool HasThePosition(Vector3 createPos)
    {
        for(int i = 0; i < itemPositionList.Count; i++)
        {
            if(createPos==itemPositionList[i])
            {
                return true;
            }
        }
        return false;
    }

    //产生敌人的方法
    private void CreateEnemy()
    {
        int num = Random.Range(0, 3);//0 1 2
        Vector3 EnemyPos = new Vector3();
        if (num == 0)
        {
            EnemyPos = new Vector3(-10, 8, 0);
        }
        else if (num == 1)
        {
            EnemyPos = new Vector3(0, 8, 0);
        }
        else
        {
            EnemyPos = new Vector3(10, 8, 0);
        }
        CreateItem(item[3], EnemyPos, Quaternion.identity);
    }
}
