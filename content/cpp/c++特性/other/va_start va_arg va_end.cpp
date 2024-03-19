#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
#if 1
void print_vars(int num1, ...) {  
    va_list va_args;  
    va_start(va_args, num1);

    int num2 = va_arg(va_args, int);  
    double num3 = va_arg(va_args, double);

    printf("Num1: %d, Num2: %d, Num3: %lf\n", num1, num2, num3);

    // 不调用 va_end，编译器会报错  
    // 因为 print_vars 函数未结束，编译器不知道何时停止  
}

int main() {  
    print_vars(1, 2, 3.5);  
    return 0;  
}

#elif 1
//c参数类型，参数个数不确定。
int Sum(int Num, ...)
{
    int S = 0, T;
    va_list ap;//声明一个变量来转换参数列表
    va_start(ap, Num);//初始化变量
    for (int i = 0; i<Num; ++i)
    {
        S+=T=va_arg(ap, int);//取出参数
    }
    va_end(ap);//结束变量列表 和va_start成对使用
    return S;
}
int main()
{
    printf("%d\n", Sum(10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
    return 0;
}
#endif

/*
va_start：初始化va_list变量。在使用可变参数列表之前，需要先调用这个宏。它接受一个参数，即可变参数列表的起始位置。例如：
va_start(va_args, num1);  
在这个例子中，va_args是一个va_list类型的变量，num1是固定参数。通过调用va_start，我们告诉编译器接下来将处理可变参数列表。

va_arg：获取可变参数列表中的下一个参数。在使用va_arg时，请确保已经调用了va_start。va_arg接受一个类型修饰符（如int、double等），以指示下一个可变参数的类型。例如：
int num2 = va_arg(va_args, int);  
在这个例子中，我们获取了可变参数列表中的下一个整数值（num2）。

va_end：结束处理可变参数列表。在获取所有可变参数后，需要调用这个宏来结束可变参数列表的遍历。例如：
va_end(va_args);  
确保在调用va_end之前已经获取了所有需要的可变参数。
*/