using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//人物之间的切换 1/2/3切换1/2/3号人 按4再按1/2/3则会切换4/5/6号人 按5再按1/2/3则会切换7/8/9号人
public class Player_Change : MonoBehaviour
{
    public bool FourButtonDown = false;
    public bool FiveButtonDown = false;

    public GameObject Now_Person;

    public GameObject Person1;
    public GameObject Person2;
    public GameObject Person3;
    public GameObject Person4;
    public GameObject Person5;
    public GameObject Person6;
    public GameObject Person7;
    public GameObject Person8;
    public GameObject Person9;

    public GameObject Temp_Person1;
    public GameObject Temp_Person2;
    public GameObject Temp_Person3;

    void Awake()
    {
        Init_PersonData();//初始化人物切换数据
    }

    //初始化人物切换数据
    void Init_PersonData()
    {
        Now_Person = Person1;
        Now_Person.SetActive(true);
        Temp_Person1 = Person1;
        Temp_Person2 = Person2;
        Temp_Person3 = Person3;
    }

    void Start()
    {

    }

    void Update()
    {
        //按下1/2/3 切换相应角色
        if (Input.GetKeyDown(KeyCode.Alpha1))
        {
            Now_Person .SetActive(false);
            Now_Person = Temp_Person1;
            Now_Person.SetActive(true);
        }
        if (Input.GetKeyDown(KeyCode.Alpha2))
        {
            Now_Person.SetActive(false);
            Now_Person = Temp_Person2;
            Now_Person.SetActive(true);
        }
        if (Input.GetKeyDown(KeyCode.Alpha3))
        {
            Now_Person.SetActive(false);
            Now_Person = Temp_Person3;
            Now_Person.SetActive(true);
        }
        //按下4 切换一轮角色
        if (Input.GetKeyDown(KeyCode.Alpha4))
        {
            FiveButtonDown = false;
            FourButtonDown = !FourButtonDown;
        }
        //按下5 切换二轮角色
        if (Input.GetKeyDown(KeyCode.Alpha5))
        {
            FourButtonDown = false;
            FiveButtonDown = !FiveButtonDown;
        }
        //进行相对应更迭
        if (FourButtonDown && !FiveButtonDown)
        {
            Temp_Person1 = Person4;
            Temp_Person2 = Person5;
            Temp_Person3 = Person6;
        }
        else if (!FourButtonDown && FiveButtonDown)
        {
            Temp_Person1 = Person7;
            Temp_Person2 = Person8;
            Temp_Person3 = Person9;
        }
        else
        {
            Temp_Person1 = Person1;
            Temp_Person2 = Person2;
            Temp_Person3 = Person3;
        }
    }
}
