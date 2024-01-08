using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//敌人孵化器
public class EnemySpawner : MonoBehaviour
{
    public static int CountEnemyAlive = 0;
    public Wave[] waves;//需要有[System.Serializable]才会显示
    public Transform START;//设定初始位置出生点
    public float waveRate = 0.3f;//设定每一波出现的时间间隔
    private Coroutine coroutine;//引入协程暂停
    private void Start()
    {
        coroutine = StartCoroutine(SpawnEnemy());
    }

    //游戏失败停止的方法
    public void Stop()
    {
        StopCoroutine(coroutine);
    }

    //每一波敌人的生成
    IEnumerator SpawnEnemy()//便利每一波敌人
    {
        foreach(Wave wave in waves)
        {
            for(int i = 0; i < wave.count; i++)
            {
                GameObject.Instantiate(wave.EnemyPrefab, START.position, Quaternion.identity);//开始位置生成 不旋转
                CountEnemyAlive++;
                if(i!=wave.count-1)
                    yield return new WaitForSeconds(wave.rate);//每一个内置cd
            }
            while (CountEnemyAlive > 0)
            {
                yield return 0;
            }
            yield return new WaitForSeconds(waveRate);//每一波cd
        }
        while (CountEnemyAlive > 0)
        {
            //还有敌人存活
            yield return 0;
        }
        GameManager.Instance.Win();//调用胜利方法
    }

}
