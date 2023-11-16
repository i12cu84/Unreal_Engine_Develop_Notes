#include <stdio.h>
int main()
{
    #ifdef __STDC__
    printf("标准C代码文件\n");
    #else
    printf("非标准C代码文件\n");
    #endif
    return 0;
}

/*
当要求程序严格遵循 ANSIC 标准时该标识符被赋值为 1 ，主要是判断我们的程序文件是不是标准 C 程序
*/