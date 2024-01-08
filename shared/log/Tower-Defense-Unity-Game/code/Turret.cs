using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//炮台攻击判定和触发特效
public class Turret : MonoBehaviour
{
    private List<GameObject> enemys = new List<GameObject>();

    private void OnTriggerEnter(Collider col)//如果进入范围
    {
        if (col.tag == "Enemy")//对标签(tag)是Enemy的敌人计入链表
        {
            enemys.Add(col.gameObject);
        }
    }

    private void OnTriggerExit(Collider col)//如果离开范围
    {
        if (col.tag == "Enemy")//对标签(tag)是Enemy的敌人移除链表
        {
            enemys.Remove(col.gameObject);
        }
    }

    //默认攻击第一个
    public float attackRateTime = 1;//多少秒攻击一次
    private float timer = 0;

    public GameObject bulletPrefab;//实例化炮弹
    public Transform firePosition;//子弹的位置
    public Transform head;//炮台头部方向

    public bool useLaser = false;//初始默认不是第一种炮台的激光攻击方式
    public float damageRate = 70;//激光的一秒钟造成70伤害
    public LineRenderer laserRenderer;//激光发射控件
    public GameObject laserEffect;//激光造成伤害特效
    private void Start()
    {
        timer = attackRateTime;//初始情况有子弹
    }

    private void Update()
    {
        //调整方向 朝向敌人
        if (enemys.Count > 0 && enemys[0] != null)
        {
            Vector3 targetPosition = enemys[0].transform.position;//获取第一个攻击敌人的位置
            targetPosition.y = head.position.y;//高度上保持一致
            head.LookAt(targetPosition);
        }
        if (!useLaser)//不使用激光攻击方式
        {
            //第二种第三种炮台攻击方式
            //开始攻击敌人
            timer += Time.deltaTime;//这里强制类型转换了 不知道会不会出问题
            if (enemys.Count > 0 && timer >= attackRateTime)//cd结束
            {
                timer = 0;//cd清零
                Attack();//触发攻击
            }
        }
        else if (enemys.Count > 0)//附近有敌人才进行激光攻击
        {
            if (laserRenderer.enabled == false)//重置
            {
                laserRenderer.enabled = true;
            }
            laserEffect.SetActive(true);//激光特效
            //第一种炮台的激光攻击方式
            if (enemys[0] == null)//如果第一个敌人消失或被破坏
            {
                UpdateEnemys();//更新List
            }
            if (enemys.Count > 0)
            {
                //才攻击第一个敌人
                laserRenderer.SetPositions(new Vector3[] { firePosition.position, enemys[0].transform.position });
                enemys[0].GetComponent<Enemy>().TakeDamage(damageRate*Time.deltaTime);//得到第一个敌人的脚本从而引用TakeDamaage造成伤害
                laserEffect.transform.position = enemys[0].transform.position;//朝向敌人
                Vector3 pos = transform.position;//获取炮台位置
                pos.y = enemys[0].transform.position.y;//y轴保持在敌人不变
                laserEffect.transform.LookAt(pos);//特效朝向炮台
            }
        }
        else
        {
            laserEffect.SetActive(false);//禁用特效
            laserRenderer.enabled = false;//暂停攻击
        }
    }

    
    void Attack()
    {
        if (enemys[0] == null)//如果第一个敌人消失或被破坏
        {
            UpdateEnemys();//更新List
        }
        if (enemys.Count > 0)
        {
            GameObject bullet = GameObject.Instantiate(bulletPrefab, firePosition.position, firePosition.rotation);//对应旋转
            bullet.GetComponent<Bullet>().SetTarget(enemys[0].transform);
        }
        else
        {
            timer = attackRateTime;//没有敌人 则待续储蓄子弹
        }
    }

    void UpdateEnemys()//更新List
    {
        //移除所有为空的List元素
        List<int> emptyIndex = new List<int>();
        for (int index = 0; index < enemys.Count; index++)
        {
            if (enemys[index] == null)
            {
                emptyIndex.Add(index);
            }
        }
        for(int i = 0; i < emptyIndex.Count; i++)
        {
            enemys.RemoveAt(emptyIndex[i]-i);//集合中移除
        }
        //另一种思路 RemoveAll(c=>c.gameObject==null)
    }

}
