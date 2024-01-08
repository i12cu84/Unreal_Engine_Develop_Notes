using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//子弹信息
public class BulletAttr : MonoBehaviour
{
    public int speed;//子弹速度
    public int damage;//伤害
    public GameObject webPrefab;//网格

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.tag == "Broder")//边界销毁自身
        {
            Destroy(gameObject);
        }
        else if (collision.tag == "Fish")//碰到鱼销毁自身变成网
        {
            GameObject web = Instantiate(webPrefab);
            web.transform.SetParent(gameObject.transform.parent, false);//
            web.transform.position = gameObject.transform.position;//网位置设为子弹自身位置
            web.GetComponent<WebAttr>().damage = damage;//获取伤害
            Destroy(gameObject);
        }
    }
    void Start()
    {
        
    }

    void Update()
    {
        
    }
}
