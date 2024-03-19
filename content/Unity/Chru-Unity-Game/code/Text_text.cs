using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
//用于测试的脚本
public class Text_text : MonoBehaviour
{
    public UnityEngine.KeyCode Key = KeyCode.Space;

    public Text _text_;

    private static Text_text _instance;
    public static Text_text Instance//其他方法以该方法调用获值
    {
        get
        {
            return _instance;
        }
    }

    void Awake()
    {
        _instance = this;
        Key = KeyCode.Space;
    }

    void Start()
    {
        
    }

    //void OnGUI()
    //{
    ////    if (Input.anyKeyDown)
    ////    {
    ////        Event e = Event.current;
    ////        if (e.isKey)
    ////        {
    ////            Key = e.keyCode;
    ////        }
    ////    }
    //}

    void FixedUpdate()
    {
        Key = getKeyDownCode();
        _text_.text = Key.ToString();
    }

    public KeyCode getKeyDownCode()
    {
        if (Input.anyKeyDown)
        {
            foreach (KeyCode keyCode in Enum.GetValues(typeof(KeyCode)))
            {
                if (Input.GetKeyDown(keyCode))
                {
                    //Debug.Log(keyCode.ToString());//输出显示的按键
                    return keyCode;
                }
            }
        }
        return KeyCode.None;
    }

    void Update()
    {

    }

}
