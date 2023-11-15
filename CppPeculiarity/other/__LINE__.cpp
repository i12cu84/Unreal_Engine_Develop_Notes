#include <iostream>
#define GETCODELINE(fmt,...) (printf(fmt"line:%d \n",##__VA_ARGS__,__LINE__));
int main()
{
    //可变参数
    GETCODELINE("%s ","显示当前函数");// ok

    //字符串常量
    GETCODELINE();// ok
    return 0;
}