using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//玩家的方法
public class Player : MonoBehaviour
{
    //属性值
    public float moveSpeed = 3;//设定速度
    private Vector3 bullectEulerAngles;//子弹朝向
    private float timeVal;//计时器 发射cd
    private float defendTimeVal=5;//保护状态时间
    private bool isDefended=true;//处于被保护状态


    //引用
    private SpriteRenderer sr;//渲染器的引用
    public Sprite[] tankSprite;//上右下左
    public GameObject bullectPrefab;//引用子弹
    public GameObject explosionPrefab;//引用爆炸特效
    public GameObject defendEffectPrefab;//受保护特效

    private void Awake()
    {
        sr = GetComponent<SpriteRenderer>();//拿到渲染组件
    }
    void Start()
    {

    }

    void Update()
    {
        //是否处于无敌状态
        if (isDefended)
        {
            defendEffectPrefab.SetActive(true);
            defendTimeVal -= Time.deltaTime;
            if (defendTimeVal <= 0)
            {
                isDefended = false;
                defendEffectPrefab.SetActive(false);
            }
        }

    }

    private void FixedUpdate()//固定物理帧
    {
        if (PlayerManager.Instance.isDefeat)//基地被破坏 不能操作了
        {
            return;
        }
        Move();//移动方法
        //由于放在FixedUpdate里发射体感不好 因此放在Update里
        //攻击的cd
        if (timeVal > 0.4f)
        {
            Attack();//攻击方法
        }
        else
        {
            timeVal += Time.fixedDeltaTime;//随时间累积
        }
    }

    //坦克的攻击方法
    private void Attack()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            //子弹产生的角度 当前坦克的角度+子弹应该旋转的角度
            Instantiate(bullectPrefab, transform.position, Quaternion.Euler(transform.eulerAngles+bullectEulerAngles)) ;
            timeVal = 0;//发射冷却归0
        }
    }

    //坦克的移动方法
    private void Move()
    {
        float v = Input.GetAxisRaw("Vertical");//垂直移动
        transform.Translate(Vector3.up * v * moveSpeed * Time.fixedDeltaTime, Space.World);
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

        float h = Input.GetAxisRaw("Horizontal");//水平移动
        transform.Translate(Vector3.right * h * moveSpeed * Time.fixedDeltaTime, Space.World);
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
        if (isDefended)
        {
            return;
        }
        //玩家阵亡 不存在
        PlayerManager.Instance.isDead = true;
        //产生爆炸特效
        Instantiate(explosionPrefab, transform.position, transform.rotation);
        //死亡销毁
        Destroy(gameObject);
    }
}
