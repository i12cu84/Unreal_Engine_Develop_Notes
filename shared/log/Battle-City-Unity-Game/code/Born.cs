using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Born : MonoBehaviour
{
    public GameObject playerPrefab;
    public GameObject[] enemyPrefabList;
    public bool createPlayer=false;
    void Start()
    {
        Invoke("BornTank", 1f);//延时调用方法
        Destroy(gameObject, 1f);//延时调用销毁
    }

    void Update()
    {
        
    }

    private void BornTank()
    {
        if (createPlayer)
        {
            Instantiate(playerPrefab, transform.position, Quaternion.identity);
        }
        else
        {
            int num = Random.Range(0, 2);
            Instantiate(enemyPrefabList[num], transform.position, Quaternion.identity);
        }
    }
}
