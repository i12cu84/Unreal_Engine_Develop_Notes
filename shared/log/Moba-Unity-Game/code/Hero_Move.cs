using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;//NavMeshAgent AI方式移动
public class Hero_Move : MonoBehaviour
{
    public NavMeshAgent agent;//NavMeshAgents是一个组件
    public Animator anim;//动画组件 用于修改速度
    void Start()
    {
        
    }

    void Update()
    {
        if (Input.GetMouseButtonDown(0))//左键按下
        {
            //射线检测
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);//获取到射线
            RaycastHit hit;//保存碰撞信息
            if (Physics.Raycast(ray, out hit))//如果发生碰撞 返回out参数
            {
                //hit.point
                //print(hit.point);
                agent.SetDestination(hit.point);//点击位置
            }
        }
        anim.SetFloat("speed", agent.velocity.magnitude);
    }
}
