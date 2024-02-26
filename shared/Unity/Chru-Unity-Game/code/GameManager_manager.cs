using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;//加载场景
//manager设置 游戏界面与UI等设计
public class GameManager_manager : MonoBehaviour
{
    public int WorldTime = 1;//世界速度1倍速
    public bool IsSetting = false;//是否切换设置

    public GameObject Bg;//设置

    public Button ControlButton;//控制按钮
    public Image ControlImage;//控制图片
    public Slider Zoom_Slider;//鼠标缩放灵敏度
    public Slider Endlong_Slider;//鼠标纵向灵敏度
    public Slider Across_Slider;//鼠标横向灵敏度
    public Text Zoom_Text;//鼠标缩放灵敏度数值
    public Text Endlong_Text;//鼠标纵向灵敏度数值
    public Text Across_Text;//鼠标横向灵敏度数值
    public float Mouse_Zoom_Coefficient = 1f;//鼠标缩放灵敏度系数
    public float Mouse_Endlong_Coefficient = 1f;//鼠标纵向灵敏度系数
    public float Mouse_Across_Coefficient = 1f;//鼠标横向灵敏度系数

    public Button KeyButton;//按键按钮
    public Image KeyImage;//按钮图片
    public KeyCode KeyCode_Temp;//获取的临时按键
    public KeyCode First_Key = KeyCode.Alpha1;//第一切换
    public KeyCode Second_Key = KeyCode.Alpha2;//第二切换
    public KeyCode Third_Key = KeyCode.Alpha3;//第三切换
    public KeyCode Change2_Key = KeyCode.Alpha4;//切换第二组
    public KeyCode Change3_Key = KeyCode.Alpha5;//切换第三组
    public KeyCode Jump_Key = KeyCode.Space;//跳跃按键
    public KeyCode Shift_Key = KeyCode.LeftShift;//冲刺按钮
    public Text First_Text;//切换按键
    public Text Second_Text;//切换按键
    public Text Third_Text;//切换按键
    public Text Change2_Text;//切换按键
    public Text Change3_Text;//切换按键
    public Text Jump_Text;//切换按键
    public Text Shift_Text;//切换按键
    public int ChangeButtonDownNum = 0;//按下修改按键的次数(修改成功后置0
    public float NumTimer = 0;//超时跳出 
    public InputField First_InputField;

    public Button VoiceButton;//声音按钮
    public Image VoiceImage;//声音图片
    public Slider All_Slider;//全局音量
    public Slider Bg_Slider;//bgm音量
    public Text All_Text;//全局音量数值
    public Text Bg_Text;//bgm音量数值
    public float All_volume = 1f;//全局音量
    public float Bg_volume = 1f;//bgm音量

    public Button OtherButton;//其他按钮
    public Image OtherImage;//其他图片
    public Camera My_Eyes;//视角控件
    public GameObject OneSee_Tf;//第一人称的My_Eyes的坐标设定
    public GameObject ThreeSee_Tf;//第三人称的My_Eyes的坐标设定
    public Button OneSee_Button;//设为第一视角的按钮
    public Button ThreeSee_Button;//设为第三视角的按钮
    public bool OneSee = true;//是否第一人称
    public bool ThreeSee = false;//是否第三人称

    public Button BackButton;//返回按钮

    public Text TitleText;//画布标题

    //实例化
    private static GameManager_manager _instance;
    public static GameManager_manager Instance//其他方法以该方法调用获值
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
        Mouse_Zoom_Coefficient = 1f;//鼠标缩放灵敏度系数
        Mouse_Endlong_Coefficient = 1f;//鼠标纵向灵敏度系数
        Mouse_Across_Coefficient = 1f;//鼠标横向灵敏度系数
        First_Key = KeyCode.Alpha1;//第一切换
        Second_Key = KeyCode.Alpha2;//第二切换
        Third_Key = KeyCode.Alpha3;//第三切换
        Change2_Key = KeyCode.Alpha4;//切换第二组
        Change3_Key = KeyCode.Alpha5;//切换第三组
        Jump_Key = KeyCode.Space;//跳跃按键
        Shift_Key = KeyCode.LeftShift;//冲刺按钮
    }

    void Start()
    {

    }

    void Update()
    {
        GetSetting();//呼出设置
    }

    //呼出设置
    public void GetSetting()
    {
        //是否呼出setting
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            if (IsSetting == false)//正常世界 打开setting
            {
                IsSetting = true;//在设置中
                WorldTime = 0;//世界暂停
                Bg.SetActive(true);//弹出Setting
                TitleText.text = "Setting";//显示标题为设置
            }
            else
            {
                IsSetting = false;//不在设置中
                WorldTime = 1;//世界恢复
                Bg.SetActive(false);//弹走Setting
                ButtonBeWhite();//按钮恢复白色 设置全部隐藏
            }
        }
        if (IsSetting == true)//正处于设置当中
        {
            Setting_Change();//设置有所更改
        }
    }

    //按钮恢复白色 设置全部隐藏
    public void ButtonBeWhite()
    {
        //恢复白色
        ControlButton.image.color = Color.white;
        KeyButton.image.color = Color.white;
        VoiceButton.image.color = Color.white;
        OtherButton.image.color = Color.white;
        //设置隐藏
        ControlImage.gameObject.SetActive(false);
        KeyImage.gameObject.SetActive(false);
        VoiceImage.gameObject.SetActive(false);
        OtherImage.gameObject.SetActive(false);
    }

    //设置有所更改
    public void Setting_Change()
    {
        ControlButton_Setting();//ControlButton下的设置更新
        KeyButton_Setting();//KeyButton_Setting下的设置更新
        VoiceButton_Setting();//VoiceButton_Setting下的设置更新
        OtherButton_Setting();//OtherButton_Setting下的设置更新
    }

    //ControlButton下的设置更新
    public void ControlButton_Setting()
    {
        Mouse_Zoom_Coefficient = Zoom_Slider.value;//鼠标缩放灵敏度系数
        Zoom_Text.text = (Mouse_Zoom_Coefficient * 100f).ToString("0");//显示灵敏度数值

        Mouse_Endlong_Coefficient = Endlong_Slider.value;//鼠标纵向灵敏度系数
        Endlong_Text.text = (Mouse_Endlong_Coefficient * 100f).ToString("0");//显示灵敏度数值

        Mouse_Across_Coefficient = Across_Slider.value;//鼠标横向灵敏度系数
        Across_Text.text = (Mouse_Across_Coefficient * 100f).ToString("0");//显示灵敏度数值
    }

    // KeyButton下的设置更新
    public void KeyButton_Setting()
    {
        //如果输入中输入了 则进行一系列的按钮修改
        First_InputField_WriteDwon();
    }

    /*
    ////查看更改成了哪个按键
    //public KeyCode getKeyDownCode()
    //{
    //    if (Input.anyKeyDown)
    //    {
    //        foreach (KeyCode keyCode in Enum.GetValues(typeof(KeyCode)))
    //        {
    //            if (Input.GetKeyDown(keyCode))
    //            {
    //                Debug.Log(keyCode.ToString());
    //                return keyCode;
    //            }
    //        }
    //    }
    //    return KeyCode.None;
    //}
    //
    //使用按钮方案 不可取
    ////First的按钮
    //public void FirstButtonDown()
    //{
    //    ChangeButtonDownNum++;//按下次数+1
    //    if (ChangeButtonDownNum > 1)//由于没有置0 因此 不进入设置环境
    //    {
    //        return;
    //    }
    //    First_Text.text = " ";
    //    while (true)
    //    {
    //        NumTimer += Time.deltaTime;
    //        if (NumTimer > 10000f)
    //        {
    //            Debug.Log(NumTimer);
    //            First_Text.text = First_Key.ToString();
    //            return;
    //        }
    //        if (Input.anyKeyDown)
    //        {
    //            foreach (KeyCode keyCode in Enum.GetValues(typeof(KeyCode)))
    //            {
    //                if (Input.GetKeyDown(keyCode))
    //                {
    //                    //Debug.Log(keyCode.ToString());
    //                    //return keyCode;
    //                    First_Key = keyCode;
    //                    First_Text.text = First_Key.ToString();
    //                    ChangeButtonDownNum = 0;//置0 退出设置环境
    //                    return;
    //                }
    //            }
    //        }
    //    }
    //}
    //
    ////Second的按钮
    //
    ////Third的按钮
    //
    ////Change2的按钮
    //
    ////Change3的按钮
    //
    ////Jump的按钮
    //
    ////Shift的按钮
    */

    //修改到此 目地是将 输入的文本 更改成当前需要按键的按钮 相应的keycode
    //public void First_InputField_WriteDwon()
    //{
    //    if(First_InputField.text!="")//如果非空 则进行修改按键
    //    {
    //        //First_Key = First_InputField.text;
    //    }
    //}

    //VoiceButton下的设置更新
    public void VoiceButton_Setting()
    {
        All_volume = All_Slider.value;//总音量系数
        All_Text.text = (All_volume * 100f).ToString("0");//显示总音量数值

        Bg_volume = Bg_Slider.value;//bgm音量系数
        Bg_Text.text = (Bg_volume * 100f).ToString("0");//bgm总音量
    }

    //bgm是否开启
    void BgmOpen()
    {

    }

    //OtherButton下的设置更新
    public void OtherButton_Setting()
    {

    }

    //按下 设为第一人称的按钮
    public void OneSeeButtonDown()
    {
        OneSee = true;//是第一人称
        ThreeSee = false;//不是第三人称
        My_Eyes.transform.position = OneSee_Tf.transform.position;//设为第一人称位置
    }

    //按下 设为第三人称的按钮
    public void ThreeSeeButtonDown()
    {
        OneSee = false;//不是第一人称
        ThreeSee = true;//是第三人称
        My_Eyes.transform.position = ThreeSee_Tf.transform.position;//设为第三人称位置
    }

    //ControlButton 控制设置
    public void ControlButtonDown()
    {
        ButtonBeWhite();//按钮恢复白色
        ControlButton.image.color = Color.red;//颜色变红表示被选中
        TitleText.text = "Control";//显示标题为控制
        ControlImage.gameObject.SetActive(true);//设置显示
    }

    //KeyButton 按键设置
    public void KeyButtonDown()
    {
        ButtonBeWhite();//按钮恢复白色
        KeyButton.image.color = Color.red;//颜色变红表示被选中
        TitleText.text = "Key";//显示标题为按键
        KeyImage.gameObject.SetActive(true);//设置显示
    }

    //VoiceButton 声音设置
    public void VoiceButtonDown()
    {
        ButtonBeWhite();//按钮恢复白色
        VoiceButton.image.color = Color.red;//颜色变红表示被选中
        TitleText.text = "Voice";//显示标题为声音
        VoiceImage.gameObject.SetActive(true);//设置显示
    }

    //OtherButton 其他设置
    public void OtherButtonDown()
    {
        ButtonBeWhite();//按钮恢复白色
        OtherButton.image.color = Color.red;//颜色变红表示被选中
        TitleText.text = "Other";//显示标题为其他
        OtherImage.gameObject.SetActive(true);//设置显示
    }

    //返回到场景0开始界面
    public void BackButtonDown()
    {
        SceneManager.LoadScene(0);//传送到1场景
    }

}
