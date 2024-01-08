using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//pacman的移动脚本
//ctrl+k+f整理
public class PacmanMove : MonoBehaviour
{
    public float speed = 0.35f;//移动速度
    private Vector2 dest = Vector2.zero;//下一次去的目的地方向

    void Start()
    {
        dest = this.transform.position;//目的地设为自身

    }

    void FixedUpdate() //锁帧来同步游戏速度
    {
        //插值得到要移动到dest位置的下一次坐标
        Vector2 temp = Vector2.MoveTowards(transform.position, dest, speed);//位置 方向 速度 返回值方向距离
        //通过刚体来设置物体的位置
        GetComponent<Rigidbody2D>().MovePosition(temp);//移动
        //必须先达到上一个dest的位置才可以发出新的目的地设置指令
        if ((Vector2)transform.position == dest)
        {
            //按键检测
            //上
            if ((Input.GetKey(KeyCode.UpArrow) || Input.GetKey(KeyCode.W)) && Valid(Vector2.up))
            {
                dest = (Vector2)transform.position + Vector2.up;//加一个向上的单位
            }
            //下
            if ((Input.GetKey(KeyCode.DownArrow) || Input.GetKey(KeyCode.S)) && Valid(Vector2.down))
            {
                dest = (Vector2)transform.position + Vector2.down;//加一个向下的单位
            }
            //左
            if ((Input.GetKey(KeyCode.LeftArrow) || Input.GetKey(KeyCode.A)) && Valid(Vector2.left))
            {
                dest = (Vector2)transform.position + Vector2.left;//加一个向左的单位
            }
            //右
            if ((Input.GetKey(KeyCode.RightArrow) || Input.GetKey(KeyCode.D)) && Valid(Vector2.right))
            {
                dest = (Vector2)transform.position + Vector2.right;//加一个向右的单位
            }
            //获取移动方向
            Vector2 dir = dest - (Vector2)transform.position;//走向的向量
            //把获取到的移动方向设置给动画状态机
            GetComponent<Animator>().SetFloat("Dirx", dir.x);//左右
            GetComponent<Animator>().SetFloat("Diry", dir.y);//上下
        }
    }

    //检测将要去的位置是否可以到达
    private bool Valid(Vector2 dir)//传入将要去的地点
    {
        //记录下当前位置
        Vector2 pos = transform.position;//记录当前的值
        //将要到达的位置向当前位置发射一条射线 并储存下射线信息
        RaycastHit2D hit = Physics2D.Linecast(pos + dir, pos);//将要去的到当前的地方打一个射线
        //返回此射线是否打到了吃豆人自身上的碰撞器
        return (hit.collider == GetComponent<Collider2D>());//射线的碰撞器是否打得到碰撞器
    }
}
