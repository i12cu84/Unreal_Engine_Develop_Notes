using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//敌人的方法
public class Enemys : MonoBehaviour
{
    //属性值
    public float moveSpeed = 3;//设定速度
    private Vector3 bullectEulerAngles;//子弹朝向
    private float v=-1;
    private float h=0;

    //引用
    private SpriteRenderer sr;//渲染器的引用
    public Sprite[] tankSprite;//上右下左
    public GameObject bullectPrefab;//引用子弹
    public GameObject explosionPrefab;//引用爆炸特效

    //计时器
    private float timeVal;//计时器 发射cd
    private float timeValChangeDirection=0;//改变方向计时器

    private void Awake()
    {
        sr = GetComponent<SpriteRenderer>();//拿到渲染组件
    }
    void Start()
    {

    }

    void Update()
    {

        //攻击的时间间隔
        if (timeVal > 3f)
        {
            Attack();//攻击方法
        }
        else
        {
            timeVal += Time.deltaTime;//随时间恢复CD
        }
    }

    private void FixedUpdate()//固定物理帧
    {
        Move();//移动方法
        //Attack();//攻击方法
        //由于放在FixedUpdate里发射体感不好 因此放在Update里
    }

    //坦克的攻击方法
    private void Attack()
    {
        //子弹产生的角度 当前坦克的角度+子弹应该旋转的角度
        Instantiate(bullectPrefab, transform.position, Quaternion.Euler(transform.eulerAngles + bullectEulerAngles));
        timeVal = 0;//发射冷却归0
    }

    //坦克的移动方法
    private void Move()
    {
        transform.Translate(Vector3.up * v * moveSpeed * Time.fixedDeltaTime, Space.World);
        transform.Translate(Vector3.right * h * moveSpeed * Time.fixedDeltaTime, Space.World);
        if (timeValChangeDirection >= 4)
        {
            int num = Random.Range(0, 8);
            if (num > 5)//设定大概率向下行走
            {
                v = -1;
                h = 0;
            }
            else if(num==0)
            {
                v = 1;
                h = 0;
            }
            else if(num>0 && num<=2)
            {
                v = 0;
                h = -1;
            }
            else
            {
                v = 0;
                h = 1;
            }
            timeValChangeDirection = 0;//归零
        }
        else
        {
            timeValChangeDirection += Time.fixedDeltaTime;
        }
        if (v < 0)//下
        {
            sr.sprite = tankSprite[2];
            bullectEulerAngles = new Vector3(0, 0, -180);

        }
        else if (v > 0)//上
        {
            sr.sprite = tankSprite[0];
            bullectEulerAngles = new Vector3(0, 0, 0);
        }

        if (v != 0)
        {
            return;
        }

        if (h < 0)//左
        {
            sr.sprite = tankSprite[3];
            bullectEulerAngles = new Vector3(0, 0, 90);
        }
        else if (h > 0)//右
        {
            sr.sprite = tankSprite[1];
            bullectEulerAngles = new Vector3(0, 0, -90);
        }
    }

    //坦克的死亡方法
    private void Die()
    {
        //玩家得分+1
        PlayerManager.Instance.playerScore++;
        //产生爆炸特效
        Instantiate(explosionPrefab, transform.position, transform.rotation);
        //死亡销毁
        Destroy(gameObject);
    }

    //如果相撞 做出一定反应
    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Enemy")
        {
            timeValChangeDirection = 4;
        }
    }
}
