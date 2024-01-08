using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
//bag背包 游戏界面与UI等设计
public class GameManager_bag : MonoBehaviour
{
    public int WorldTime = 1;//世界速度1倍速
    public bool IsSetting = false;//是否处于切换背包

    public GameObject Bag;//背包

    public Button WeaponButton;//武器按钮
    public Image WeaponImage;//武器栏

    public Button AomorButton;//防具按钮
    public Image AomorImage;//防具栏目

    public Button PropButton;//道具按钮
    public Image PropImage;//道具栏目

    public Button MaterialsButton;//材料按钮
    public Image MaterialsImage;//材料栏目

    public Text TitleText;//画布标题

    //实例化
    private static GameManager_bag _instance;
    public static GameManager_bag Instance//其他方法以该方法调用获值
    {
        get
        {
            return _instance;
        }
    }

    void Awake()
    {
        _instance = this;//获得自身 初始化时便返回自身
        Init_Data();//初始化数据
    }

    //初始化数据
    void Init_Data()
    {
        WorldTime = 1;//世界速度1倍 此时未打开设置
    }

    void Start()
    {
        
    }

    void Update()
    {
        GettingBag();//呼出背包
    }

    //呼出背包
    public void GettingBag()
    {
        //是否呼出背包
        if (Input.GetKeyDown(KeyCode.B))
        {
            if (IsSetting == false)//正常世界 打开背包
            {
                IsSetting = true;//在背包中
                WorldTime = 0;//世界暂停
                Bag.SetActive(true);//弹出Bag
                TitleText.text = "Setting";//显示标题为设置
            }
            else
            {
                IsSetting = false;//不在背包中
                WorldTime = 1;//世界恢复
                Bag.SetActive(false);//弹走Bag
                ButtonBeWhite();//按钮恢复白色 设置全部隐藏
            }
        }
        if (IsSetting == true)//正处于设置当中
        {
            Bag_Change();//设置有所更改
        }
    }

    //设置有所更改
    public void Bag_Change()
    {

    }

    //按钮恢复白色 设置全部隐藏
    public void ButtonBeWhite()
    {
        //恢复白色
        WeaponButton.image.color = Color.white;
        AomorButton.image.color = Color.white;
        PropButton.image.color = Color.white;
        MaterialsButton.image.color = Color.white;
        //设置隐藏
        WeaponImage.gameObject.SetActive(false);
        AomorImage.gameObject.SetActive(false);
        PropImage.gameObject.SetActive(false);
        MaterialsImage.gameObject.SetActive(false);
    }

    //->

    //按下武器栏目按钮
    public void WeaponButtonDown()
    {
        ButtonBeWhite();//按钮恢复白色
        WeaponButton.image.color = Color.red;//颜色变红表示被选中
        TitleText.text = "Weapon";//显示标题为控制
        WeaponImage.gameObject.SetActive(true);//设置显示
    }

    //按下防具栏目按钮
    public void AomorButtonDown()
    {
        ButtonBeWhite();//按钮恢复白色
        AomorButton.image.color = Color.red;//颜色变红表示被选中
        TitleText.text = "Aomor";//显示标题为控制
        AomorImage.gameObject.SetActive(true);//设置显示
    }

    //按下道具栏目按钮
    public void PropButtonDown()
    {
        ButtonBeWhite();//按钮恢复白色
        PropButton.image.color = Color.red;//颜色变红表示被选中
        TitleText.text = "Prop";//显示标题为控制
        PropImage.gameObject.SetActive(true);//设置显示
    }

    //按下材料栏目按钮
    public void MaterialsButtonDown()
    {
        ButtonBeWhite();//按钮恢复白色
        MaterialsButton.image.color = Color.red;//颜色变红表示被选中
        TitleText.text = "Materials";//显示标题为控制
        MaterialsImage.gameObject.SetActive(true);//设置显示
    }

}
