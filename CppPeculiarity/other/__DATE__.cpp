#include <iostream>
#define GETCODELINE(fmt,...) (printf(fmt"time:%s \n",##__VA_ARGS__,__DATE__));
int main()
{
    //可变参数
    GETCODELINE("%s ","显示当前时间");// ok

    //字符串常量
    GETCODELINE();// ok
    return 0;
}