using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//人物基本行为
public class Player_Move : MonoBehaviour
{
    public float Move_Speed = 3f;//移动速度
    public float Shift_Speed = 3f;//冲刺速度
    public float Shiftcd = 1f;//冲刺cd
    public float Shiftcd_Max = 1f;//冲刺cd最大值
    public float JumpGravity = 150f;//跳跃力度
    public float Jumpcd = 1f;//跳跃cd
    public float Jumpcd_Max = 1f;//跳跃cd最大值
    public float Sensitivety_Mousewheel = 2f;//滚轮速度
    public float near = 20.0f;//滚放视野
    public float far = 100.0f;//滚放视野
    public float Mouse_Across = 15f;//横向视野转动
    public float Mouse_Endlong = 15f;//纵向视野转动

    public Camera My_Eyes;//视角
    public Rigidbody rg;//刚体
    public GameObject Forward;//前方朝向
    public GameObject Left;//左方朝向
    public GameObject ShiftImage;//冲刺图标
    public GameObject JumpImage;//跳跃图标

    void Awake()
    {

    }

    void Start()
    {
        InitData();//起始数据加载
    }

    void FixedUpdate()
    {
        Cd_Accumulation();//cd累加
        ShowcdoverUI();//显示cd好了的UI
    }

    void Update()
    {
        Move();//上下左右移动
        Move_Mousewheel();//滚轮缩放视野
        Move_Mousemove();//鼠标视角转动
        Move_Shift();//shift 鼠标右键
        Move_Jump();//跳跃
    }

    //起始数据加载
    void InitData()
    {
        Move_Speed = Player_Message.Instance.Move_Speed;//移动速度
        JumpGravity = Player_Message.Instance.JumpGravity;//跳跃力度
        Jumpcd_Max = Player_Message.Instance.Move_Jumpcd;//设定cd
        Shift_Speed = Player_Message.Instance.Move_ShiftSpeed;//冲刺速度
        Shiftcd_Max = Player_Message.Instance.Move_Shiftcd;//冲刺冷却
    }

    //cd累加
    void Cd_Accumulation()
    {
        Jumpcd += Time.fixedDeltaTime;//跳跃冷却累加
        Shiftcd += Time.fixedDeltaTime;//Shift冷却累加
    }

    //显示cd好了的UI
    void ShowcdoverUI()
    {
        if (Shiftcd >= Shiftcd_Max)
        {
            ShiftImage.SetActive(true);//显示ShiftImage的UI
        }
        if (Jumpcd >= Jumpcd_Max)
        {
            JumpImage.SetActive(true);//显示JumpImage的UI
        }
    }

    //上下左右移动
    private void Move()
    {
        float v = Input.GetAxisRaw("Vertical");//垂直移动
        transform.Translate((this.transform.position - Forward.transform.position) * v
            * Move_Speed * Time.fixedDeltaTime, Space.World);//前后移动
        float h = Input.GetAxisRaw("Horizontal");//水平移动
        transform.Translate((this.transform.position - Left.transform.position) * h *
            Move_Speed * Time.fixedDeltaTime, Space.World);//左右移动
    }

    //鼠标滚轮缩放视野
    private void Move_Mousewheel()
    {
        //My_Eyes.GetComponent<Transform>().transform.Translate();
        if (Input.GetAxis("Mouse ScrollWheel") != 0)
        {
            My_Eyes.fieldOfView = My_Eyes.fieldOfView - Input.GetAxis("Mouse ScrollWheel") * Sensitivety_Mousewheel;
            My_Eyes.fieldOfView = Mathf.Clamp(My_Eyes.fieldOfView,near * GameManager_manager.Instance.Mouse_Zoom_Coefficient, far * GameManager_manager.Instance.Mouse_Zoom_Coefficient);
                        //乘上了设置中的设置灵敏度系数
        }
    }

    //鼠标移动视野
    private void Move_Mousemove()
    {
        //视角横向移动
        float MouseX = Input.GetAxis("Mouse X");//鼠标横向移动
        float Mouse_Across_Change=Mouse_Across *MouseX * GameManager_manager.Instance.Mouse_Across_Coefficient;
        transform.localRotation = transform.localRotation * Quaternion.Euler(0, Mouse_Across_Change, 0);
        //乘上了设置中的设置灵敏度系数

        //视角纵向移动
        float MouseY = Input.GetAxis("Mouse Y");//鼠标纵向移动
        float Mouse_Endlong_Change = Mouse_Endlong * MouseY * GameManager_manager.Instance.Mouse_Endlong_Coefficient;
        My_Eyes.transform.localRotation = My_Eyes.transform.localRotation * Quaternion.Euler(-Mouse_Endlong_Change, 0, 0);
        //乘上了设置中的设置灵敏度系数
    }

    //Shift冲刺
    private void Move_Shift()
    {
        if (Shiftcd < Shiftcd_Max) return;                      //cd未好 跳过
        //shift和鼠标右键都可以触发
        if (Input.GetMouseButtonDown(1) || Input.GetKeyDown(KeyCode.LeftShift))
        {
            if (!Player_Message.Instance.Tired_Player(5)) return;   //没有体力 跳过
            ShiftImage.SetActive(false);//隐藏JumpImage的UI
            //移动
            if (Input.GetKey(KeyCode.A))//向左移动
            {
                transform.Translate(-(this.transform.position - Left.transform.position) * Shift_Speed
                    , Space.World);//左移动一码
            }
            else if (Input.GetKey(KeyCode.D))
            {
                transform.Translate((this.transform.position - Left.transform.position) * Shift_Speed
                    , Space.World);//右移动一码
            }
            else if (Input.GetKey(KeyCode.S))
            {
                transform.Translate(-(this.transform.position - Forward.transform.position) * Shift_Speed
                    , Space.World);//后移动一码
            }
            else
            {
                transform.Translate((this.transform.position - Forward.transform.position) * Shift_Speed
                    , Space.World);//前移动一码
            }
            Shiftcd = 0;//cd清零
        }
    }

    //跳跃
    private void Move_Jump()
    {
        if (Jumpcd < Jumpcd_Max) return;//cd未好 跳过
        if (Input.GetKeyDown(KeyCode.Space))
        {
            if (!(Player_Message.Instance.Tired_Player(5))) return;//没有体力 跳过
            //---为刚体的Y赋值一个新的高度,这个高度为跳跃重力,向上的力
            rg.velocity = new Vector3(rg.velocity.x, JumpGravity * Time.deltaTime, rg.velocity.z);
            JumpImage.SetActive(false);//隐藏JumpImage的UI
            Jumpcd = 0;//cd清零
        }
    }

}
