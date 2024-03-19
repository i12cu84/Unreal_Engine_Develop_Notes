#include <iostream>
using namespace std;

#include<stdio.h>
#include<stdarg.h>//ANSI C可变参数的头文件

#if 1

void myPrintf(char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

int main() {
    myPrintf("自定义 printf 函数：hello world\n");
    myPrintf("自定义 printf 函数：%s %s\n", "hello world", "C语言教程-猿说编程");
    printf("系统 printf 函数：hello world\n");
    printf("系统 printf 函数：%s %s\n", "hello world", "C语言教程-猿说编程");
    return 0;
}
#elif 1
int print(char* format, ...) {
    va_list ap;
    int n;
    va_start(ap, format);
    n = vprintf(format, ap);
    va_end(ap);
    return 0;
}

int main() {
    int ch1 = 10, ch2 = 20;
    print("%d\t%d\n%d\n", ch1, ch2, ch2);
    return 0;
}
#endif

/*
printf 函数声明：

int printf(const char *format, ...);
printf 函数将可变参数列表的格式化数据打印到标准输出（stdout）。参数 format 是包含格式字符串的 C 字符串，其格式与 printf 中的格式相同。
vprintf 函数声明：

int vprintf(const char *format, va_list arg);
vprintf 函数也用于将可变参数列表的格式化数据打印到标准输出，但是它接受一个 va_list 类型的参数 arg，该参数标识使用 va_start 初始化的变量参数列表的值。va_list 是在 <cstdarg> 中定义的特殊类型。
使用场景：

通常情况下，输出到控制台，多数情况下使用 printf 函数即可。
vprintf 函数一般和 va_start / va_end 配套使用。例如，当你需要自己编写一个自定义的 printf 函数时，可以使用 vprintf。
*/