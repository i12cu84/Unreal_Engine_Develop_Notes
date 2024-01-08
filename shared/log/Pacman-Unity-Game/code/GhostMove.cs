using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;////SceneManager.LoadScene Restart()使用 
//鬼移动脚本 启用GameManager的版本
public class GhostMove : MonoBehaviour
{
    public GameObject[] wayPointsGo;
    //储存所有路径点的transform组件
    private List<Vector3> wayPoints = new List<Vector3>();//记录路径点位置
    public float speed = 0.05f;//鬼移动速度
    //当前在前往哪个路径点的途中
    private int index = 0;//记录到当前位置
    private Vector3 startPos;//记录初始位置

    private void Start()
    {
        startPos = transform.position + new Vector3(0, 3, 0);//记录初始位置后向上移动三个单位
        //路径物体  让不同的鬼拿到不同的随机路径
        //此时 红鬼是5层 而拿第五层而-5 可以将其中 第一个索引的路径
        LoadApath(wayPointsGo[GameManager.Instance.usingIndex[GetComponent<SpriteRenderer>().sortingOrder - 5]]);
        //LoadApath(wayPointsGo[GameManager.Instance.usingIndex[GetComponent<SpriteRenderer>().sortingOrder - 2]]);//课程原函数
    }

    void FixedUpdate()
    {
        //如果还未到达目标点
        if (transform.position != wayPoints[index])
        {
            //插值得到要移动到wayPoints[indexer]位置的下一次坐标
            Vector2 temp = Vector2.MoveTowards(transform.position, wayPoints[index], speed);//位置 方向 速度 返回值方向距离
            //通过刚体来设置物体的位置
            GetComponent<Rigidbody2D>().MovePosition(temp);//移动
        }
        else
        {
            index++;
            if (index == wayPoints.Count)
            {
                index = 0;//路径置零
                LoadApath(wayPointsGo[Random.Range(0, wayPointsGo.Length)]);
            }
        }
        //获取移动方向
        Vector2 dir = wayPoints[index] - transform.position;//走向的向量
        //把获取到的移动方向设置给动画状态机
        GetComponent<Animator>().SetFloat("Dirx", dir.x);//左右
        GetComponent<Animator>().SetFloat("Diry", dir.y);//上下
    }

    //路径点存储和移动
    private void LoadApath(GameObject go)
    {
        //将上一次存放路径的路径点清空后在进行重新存储
        wayPoints.Clear();
        foreach (Transform t in go.transform)//拿出每一个组件放到t
        {
            wayPoints.Add(t.position);//存放到List中去 存放所有路径点
        }
        //不同小鬼用同一方式向上移动三个单位
        wayPoints.Insert(0, startPos);
        wayPoints.Add(startPos);
    }

    //当物体上有 bos collider 并且勾选is trigger时 在有东西进入触发器范围后调用
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.name == "Pacman")//触发触发器是否为吃豆人
        {
            if (GameManager.Instance.isSuperPacman)//如果吃豆人在超级状态
            {
                transform.position = startPos - new Vector3(0, 3, 0);//鬼变回老巢
                index = 0;
                GameManager.Instance.score += 5;//吃鬼+500分
            }
            else
            {
                collision.gameObject.SetActive(false);//停止移动
                GameManager.Instance.gamePanel.SetActive(false);//停止移动
                Instantiate(GameManager.Instance.gameoverPrefab);//游戏结束
                Invoke("ReStart", 3f);//3秒死亡动画
                Destroy(collision.gameObject);//销毁吃豆人
            }
        }
    }

    //死亡动画
    private void ReStart()
    {
        SceneManager.LoadScene(0);//加载0号场景  using UnityEngine.SceneManagement;
    }
}






////原本鬼随着指定路径进行运转的代码
//public class GhostMove : MonoBehaviour
//{
//    //储存所有路径点的transform组件
//    public Transform[] wayPoints;//记录路径点位置
//    public float speed = 0.2f;//鬼移动速度
//    //当前在前往哪个路径点的途中
//    private int index = 0;//记录到当前位置

//    void FixedUpdate()
//    {
//        //如果还未到达目标点
//        if (transform.position != wayPoints[index].position)
//        {
//            //插值得到要移动到wayPoints[indexer]位置的下一次坐标
//            Vector2 temp = Vector2.MoveTowards(transform.position, wayPoints[index].position, speed);//位置 方向 速度 返回值方向距离
//            //通过刚体来设置物体的位置
//            GetComponent<Rigidbody2D>().MovePosition(temp);//移动
//        }
//        else
//        {
//            index++;// = (index + 1) % wayPoints.Length;//越界取余返回原点
//        }
//        //获取移动方向
//        Vector2 dir = wayPoints[index].position - transform.position;//走向的向量
//        //把获取到的移动方向设置给动画状态机
//        GetComponent<Animator>().SetFloat("Dirx", dir.x);//左右
//        GetComponent<Animator>().SetFloat("Diry", dir.y);//上下
//    }


//    //当物体上有 bos collider 并且勾选is trigger时 在有东西进入触发器范围后调用
//    private void OnTriggerEnter2D(Collider2D collision)
//    {
//        if (collision.gameObject.name == "Pacman")//触发触发器是否为吃豆人
//        {
//            Destroy(collision.gameObject);//销毁吃豆人
//        }
//    }
//}
