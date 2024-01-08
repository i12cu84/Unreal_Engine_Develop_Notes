using System.Collections;//协程
using System.Collections.Generic;
using UnityEngine;
//生成鱼
public class FishMaker : MonoBehaviour
{
    public Transform fishHolder;
    public Transform[] genPosition;
    public GameObject[] fishPrefab;

    public float fishGenWaitTime = 0.5f;//每条生成间隔
    public float waveGenWaitTime = 0.3f;//每波生成间隔

    void Start()
    {
        InvokeRepeating("MakeFishe", 0, waveGenWaitTime);
        //MakeFishe();//生成一波鱼 用于测试
    }

    void Update()
    {

    }

    void MakeFishe()
    {
        int genPosIndex = Random.Range(0, genPosition.Length);//入口
        int fishPreIndex = Random.Range(0, fishPrefab.Length);//鱼钟
        int maxNum = fishPrefab[fishPreIndex].GetComponent<FishAttr>().maxNum;//获取鱼最大数量
        int maxSpeed = fishPrefab[fishPreIndex].GetComponent<FishAttr>().maxSpeed;//获取鱼最大速度
        int num = Random.Range((maxNum / 2) + 1, maxNum);//限制数量
        int speed = Random.Range(maxSpeed / 2, maxSpeed);//限制速度
        int moveType = Random.Range(0, 2);//直走 转弯
        int angOffset;//仅直走生效 直走倾斜角
        int angSpeed;//仅转弯生效 转弯角速度
        if (moveType == 0)
        {
            //直走鱼生成
            angOffset = Random.Range(-22, 22);
            //GenStraightFish(genPosIndex, fishPreIndex, num, speed, angOffset);//非协程
            StartCoroutine(GenStraightFish(genPosIndex, fishPreIndex, num, speed, angOffset));//协程
        }
        else
        {
            //转弯鱼生成
            if (Random.Range(0, 2) == 0)//50% 角速度正负
            {
                angSpeed = Random.Range(-15, -9);
            }
            else
            {
                angSpeed = Random.Range(9, 15);
            }
            StartCoroutine(GenStraightFish(genPosIndex, fishPreIndex, num, speed, angSpeed));//协程
        }
    }

    //生成直走鱼
    IEnumerator GenStraightFish(int genPosIndex, int fishPreIndex, int num, int speed, int angOffset)
    {
        for (int i = 0; i < num; i++)
        {
            GameObject fish = Instantiate(fishPrefab[fishPreIndex]);
            fish.transform.SetParent(fishHolder, false);
            fish.transform.localPosition = genPosition[genPosIndex].localPosition;
            fish.transform.localRotation = genPosition[genPosIndex].localRotation;
            fish.transform.Rotate(0, 0, angOffset);
            fish.GetComponent<SpriteRenderer>().sortingOrder += i;//就没有闪动的情况了
            fish.AddComponent<Ef_AutoMove>().speed = speed;
            yield return new WaitForSeconds(fishGenWaitTime);//间隔
        }
    }

    //生成转弯鱼
    IEnumerator GenTurnFish(int genPosIndex, int fishPreIndex, int num, int speed, int angSpeed)
    {
        for (int i = 0; i < num; i++)
        {
            GameObject fish = Instantiate(fishPrefab[fishPreIndex]);
            fish.transform.SetParent(fishHolder, false);
            fish.transform.localPosition = genPosition[genPosIndex].localPosition;
            fish.transform.localRotation = genPosition[genPosIndex].localRotation;
            fish.GetComponent<SpriteRenderer>().sortingOrder += i;//就没有闪动的情况了
            fish.AddComponent<Ef_AutoMove>().speed = speed;
            fish.AddComponent<Ef_AutoRotate>().speed = angSpeed;
            yield return new WaitForSeconds(fishGenWaitTime);//间隔
        }
    }
}
