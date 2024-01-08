using System.Collections;//协程
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;
//主游戏mian控制台 
//有一个bug是自身金币不足时 开火不足金币 金币text将无法可视 而非红黄闪动 目前解决

public class GameController : MonoBehaviour
{
    private static GameController _instance;
    public static GameController Instance//其他方法以该方法调用获值
    {
        get
        {
            return _instance;
        }
    }

    public Text oneShootCostText;//文本显示
    public Text goldText;//金币
    public Text lvText;//等级
    public Text lvNameText;//称号
    public Text smallCountdownText;//小倒计时(左下角
    public Text bigCountdownText;//大倒计时(右上角

    public Button bigCountdownButton;//倒计时拿钱
    public Button backButton;//返回
    public Button settingButton;//设置

    public Slider expSlider;//经验条

    public int lv = 0;//等级
    public int exp = 0;//经验
    public int gold = 5000;//启动金

    public const int smallCountdown = 60;//每1分钟给小钱
    public const int bigCountdown = 240;//每4分钟给大钱

    public float smallTimer = smallCountdown;//小时间
    public float bigTimer = bigCountdown;//大时间
    public Color goldColor;//金币颜色
    public int bgIndex = 0;//当前是哪一张背景图的索引

    private int costIndex = 0;//使用的是第几档炮弹 1档对应5/10  2档对应20/50
    private int[] oneShootCost = { 5, 10, 20, 50 };//每一炮所需金币和造成伤害值 每一发子弹消耗金钱数量
    private string[] lvName = { "新手", "大师" };

    public Transform bulletHolder;//子弹位置

    public Image bgImage;//背景特效
    public GameObject lvUpTips;//升级文字样式
    public GameObject fireEffect;//开火特效
    public GameObject changeEffect;//换枪特效
    public GameObject lvEffect;//升级特效
    public GameObject goldEffect;//奖金特效
    public GameObject seaWaveEffect;//浪花特效

    public Sprite[] bgSprites;//背景图片
    public GameObject[] gunGos;//枪
    public GameObject[] bullet2Gos;//子弹Prefab
    public GameObject[] bullet3Gos;

    void Awake()
    {
        _instance = this;//获得自身 初始化时便返回自身
    }

    void Start()
    {
        //恢复所有数据
        gold = PlayerPrefs.GetInt("gold", gold);
        lv = PlayerPrefs.GetInt("lv", lv);
        exp = PlayerPrefs.GetInt("exp", exp);
        smallTimer = PlayerPrefs.GetInt("scd", smallCountdown);
        bigTimer = PlayerPrefs.GetInt("bcs", bigCountdown);
        //开启载入游戏 更新恢复的数据
        UpdateUI();
    }

    void Update()
    {
        ChangeBulletCost();//调用滚轮检测 更改炮台档位
        Fire();//开火
        UpdateUI();//UI
        ChangeBg();//背景更换
    }

    //更换背景
    void ChangeBg()
    {
        if (bgIndex != lv / 20)//非零情况下设定正确值
        {
            bgIndex = lv / 20;//校准索引
            AudioManager.Instance.PlayEffectSound(AudioManager.Instance.seaWaveClip);//播放浪花音效
            Instantiate(seaWaveEffect);//浪花特效
            //bgIndex = (bgIndex >= 3) ? 3 : bgIndex;//避免等级过高越界 因此80级之后一直显示最后一个图
            //这句话出了一直出现浪花的bug
            if (bgIndex >= 3)
            {
                bgImage.sprite = bgSprites[3];
            }
            else
            {
                bgImage.sprite = bgSprites[bgIndex];
            }
        }
    }

    void UpdateUI()
    {
        bigTimer -= Time.deltaTime;
        smallTimer -= Time.deltaTime;

        //60秒后给100
        if (smallTimer <= 0)
        {
            smallTimer = smallCountdown;
            gold += 100;//直接来增加金币量
        }

        //240秒后给500
        if (bigTimer <= 0 && bigCountdownButton.gameObject.activeSelf == false)//大时间倒计时结束 且 显示满足的按钮没有出现时
        {
            bigCountdownText.gameObject.SetActive(false);//关闭倒计时显示
            bigCountdownButton.gameObject.SetActive(true);//显示满足240秒后的按钮
        }

        //经验计算换算公式 升级所需经验=100+10*当前等级
        while (exp >= 100 + 10 * lv)
        {
            lv++;//升级
            lvUpTips.SetActive(true);//显示升级框
            lvUpTips.transform.Find("Text").GetComponent<Text>().text = lv.ToString();//修改提升的等级
            StartCoroutine(lvUpTips.GetComponent<Ef_HideSelf>().HideSelf(0.5f));//0.5秒后消失
            AudioManager.Instance.PlayEffectSound(AudioManager.Instance.lvUpClip);//播放升级声音
            Instantiate(lvEffect);//升级标识特效
            exp = exp - (100 + 10 * lv);//计算剩余经验
        }
        goldText.text = "$" + gold;//输出金币量
        lvText.text = lv.ToString();//显示等级
        if (lv < 10)
        {
            lvNameText.text = lvName[0];
        }
        else
        {
            lvNameText.text = lvName[1];
        }
        smallCountdownText.text = " " + (int)smallTimer / 10 + " " + (int)smallTimer % 10;
        bigCountdownText.text = (int)bigTimer + "s";
        expSlider.value = ((float)exp) / (100 + 10 * lv);
    }

    //子弹预制体
    void Fire()
    {
        GameObject[] useBullets = bullet2Gos;
        int bulletIndex = 0;
        if (Input.GetMouseButtonDown(0) && EventSystem.current.IsPointerOverGameObject() == false)//左键按下 且没有点击游戏的物体
                                                                                                  //注:且在 Bg上Image的Raycast Target是否射线检测取消 否则会无法发射
        {
            if (gold - oneShootCost[costIndex] >= 0)//足矣放炮
            {
                //子弹选择
                switch (costIndex / 2)
                {
                    case 0: useBullets = bullet2Gos; break;
                    case 1: useBullets = bullet3Gos; break;
                }
                //bulletIndex = ((lv%10 >= 9)?9:lv%10);//一个子弹十种 这代码有点问题
                gold -= oneShootCost[costIndex];//扣钱
                AudioManager.Instance.PlayEffectSound(AudioManager.Instance.fireClip);//播放开火声音
                Instantiate(fireEffect);//开火特效
                GameObject bullet = Instantiate(useBullets[bulletIndex]);
                //子弹旋转
                bullet.transform.SetParent(bulletHolder, false);
                bullet.transform.position = gunGos[costIndex / 2].transform.Find("FirePos").transform.position;//与开火位置保持一致
                bullet.transform.rotation = gunGos[costIndex / 2].transform.Find("FirePos").transform.rotation;
                //传入子弹花费
                bullet.GetComponent<BulletAttr>().damage = oneShootCost[costIndex];
                //子弹移动
                bullet.AddComponent<Ef_AutoMove>().Dir = Vector3.up;
                bullet.GetComponent<Ef_AutoMove>().speed = bullet.GetComponent<BulletAttr>().speed;//不能写add 会冲突
            }
            else
            {
                //炮不足放炮
                StartCoroutine(GoldNotEnough());//协程引用改变text颜色 如果不用协程呢?
            }
        }
    }

    //滚轮操控炮弹档位
    void ChangeBulletCost()
    {
        if (Input.GetAxis("Mouse ScrollWheel") < 0)//向下滚轮
        {
            OnButtonMDown();
        }
        if (Input.GetAxis("Mouse ScrollWheel") > 0)//向下滚轮
        {
            OnButtonPDown();
        }
    }

    //加号按键控制炮弹档位
    public void OnButtonPDown()
    {
        gunGos[costIndex / 2].SetActive(false);//隐藏激活方式
        costIndex++;
        AudioManager.Instance.PlayEffectSound(AudioManager.Instance.changeClip);//播放换枪声音
        Instantiate(changeEffect);//换枪特效
        costIndex = (costIndex > oneShootCost.Length - 1) ? 0 : costIndex;//越界取余
        gunGos[costIndex / 2].SetActive(true);//升一档
        oneShootCostText.text = "$" + oneShootCost[costIndex];
    }

    //减号按键控制炮弹档位
    public void OnButtonMDown()
    {
        gunGos[costIndex / 2].SetActive(false);//隐藏激活方式
        costIndex--;
        AudioManager.Instance.PlayEffectSound(AudioManager.Instance.changeClip);//播放换枪声音
        Instantiate(changeEffect);//换枪特效
        costIndex = (costIndex < 0) ? oneShootCost.Length - 1 : costIndex;//越界取余
        gunGos[costIndex / 2].SetActive(true);//升一档
        oneShootCostText.text = "$" + oneShootCost[costIndex];
    }

    //按了大按钮 恢复240秒倒计时之后
    public void OnBigCountdownButtonDown()
    {
        gold += 500;
        AudioManager.Instance.PlayEffectSound(AudioManager.Instance.rewardClip);//播放获得奖励声音
        Instantiate(goldEffect);//金币特效
        bigCountdownButton.gameObject.SetActive(false);
        bigCountdownText.gameObject.SetActive(true);
        bigTimer = bigCountdown;
    }

    ////金币不足 闪动text //协程的代码  //似乎出了消失的bug
    //IEnumerator GoldNotEnough()//协程
    //{
    //    goldText.color = goldColor;//恢复原始颜色
    //    goldColor = goldText.color;//这句话会是有问题的 因为连续按左键 可能会使他存储 红色的数据
    //    goldText.color = Color.red;//变红
    //    yield return new WaitForSeconds(0.5f);//等五秒
    //    goldText.color = goldColor;//恢复原始颜色
    //}

    //自己重写的修复bug
    //金币不足 闪动text //协程的代码  //解决了该bug 但是颜色还是被变了 预估是第四个参数的不透明度的问题
    IEnumerator GoldNotEnough()//协程
    {
        goldText.color = Color.yellow;//恢复原始颜色 避免出现颜色混乱的bug附加
        goldText.color = Color.red;//变红
        yield return new WaitForSeconds(0.5f);//等五秒
        goldText.color = Color.yellow;//恢复原始颜色
    }

}
