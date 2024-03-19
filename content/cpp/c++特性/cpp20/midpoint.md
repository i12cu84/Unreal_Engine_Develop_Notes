```
#include <iostream>
#include <numeric>
int main()
{
    int a = 3;
    int b = 6;
    std::cout << "midpoint(" << a << ", " << b << "): " << std::midpoint(a, b) << '\n';
    a = 6;
    b = 3;
    std::cout << "midpoint(" << a << ", " << b << "): " << std::midpoint(a, b) << '\n';
    return 0;
}
```
std::midpoint是C++20中引入的一个函数，它用于计算两个整数、浮点数或指针的中点。以下是一些主要的特性：
整数、浮点数或指针：std::midpoint可以处理整数、浮点数或指针。
无溢出：std::midpoint计算的是a和b的一半，不会发生溢出。
四舍五入：如果a和b是整数类型，且它们的和是奇数，那么结果会向a四舍五入。
精确度：如果a和b是浮点类型，那么最多只会有一次不精确的操作。

首先定义了两个整数a和b。然后，我们使用std::midpoint(a, b)来计算它们的中点，并打印出结果。