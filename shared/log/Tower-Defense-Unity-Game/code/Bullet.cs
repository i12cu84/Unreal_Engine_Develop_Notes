using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//炮台子弹的移动
public class Bullet : MonoBehaviour
{
    public int damage = 50;
    public float speed = 40.0f;
    public GameObject explosionEffectPrefab;//爆炸特效
    private float distanceArriveTarget = 1.2f;
    private Transform target;//发射到目标位置
    public void SetTarget(Transform _target)
    {
        this.target = _target;
    }
    void Update()
    {
        if (target == null)//如果某种原因敌人不存在了
        {
            Die();
            return;//下面代码直接跳过
        }
        //子弹移动
        transform.LookAt(target.position);
        transform.Translate(Vector3.forward * speed * Time.deltaTime);
        //子弹特效
        Vector3 dir = target.position - transform.position;
        if(dir.magnitude < distanceArriveTarget)//如果接触到目标位置
        {
            target.GetComponent<Enemy>().TakeDamage(damage);
            Die();
        }
    }

    void Die()
    {
        GameObject effect = GameObject.Instantiate(explosionEffectPrefab, transform.position, transform.rotation);//触发爆炸特效
        Destroy(effect, 1);//1秒之后销毁特效
        Destroy(this.gameObject);//销毁子弹游戏物体
    }

}
