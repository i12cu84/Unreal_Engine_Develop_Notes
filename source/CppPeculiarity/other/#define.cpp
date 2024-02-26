#include <stdio.h>
#include <typeinfo>
#include <iostream>
#include <stdio.h>
#include <math.h>

#if 0
#define MAX1(x, y) ({                \
    decltype(x) _max1 = (x);         \
    decltype(y) _max2 = (y);         \
    (void) (&_max1 == &_max2);       \
    _max1 > _max2 ? _max1 : _max2; })

#define MAX2(a, b) ((a > b) ? a : b)

int main(int argc, char *argv[])
{
    int a = 1;
    float b = 1.1;
    int c = 0;
    
    c = MAX1(1,2);
    printf("max0:%d\n", c);
    
    c = MAX2(a,b);
    printf("max1:%d\n", c);

    return 0;
}

#elif 1

// 以表格形式输出一个函数的值。该程序使用了嵌套的宏
#define PI 3.141593
#define STEP (PI / 8)
#define AMPLITUDE 1.0
#define ATTENUATION 0.1 // 声波传播的衰减指数
#define DF(x) exp(-ATTENUATION *(x))
#define FUNC(x) (DF(x) * AMPLITUDE * cos(x)) // 震动衰减

// 针对函数输出：
#define STR(s) #s
#define XSTR(s) STR(s) // 将宏s展开，然后字符串化
int main()
{
    double x = 0.0;
    printf("\nFUNC(x) = %s\n", XSTR(FUNC(x)));       // 输出该函数
    printf("\n %10s %25s\n", "x", STR(y = FUNC(x))); // 表格的标题
    printf("-----------------------------------------\n");

    for (; x < 2 * PI + STEP / 2; x += STEP)
        printf("%15f %20f\n", x, FUNC(x));
    return 0;
}

#endif