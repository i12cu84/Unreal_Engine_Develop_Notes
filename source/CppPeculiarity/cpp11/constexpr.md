```
#include <iostream>
constexpr int factorial(int n)
{
    return (n <= 1) ? 1 : n * factorial(n - 1);
}
int main()
{
    constexpr int n = 5; // 编译时常量
    constexpr int result = factorial(n);
    std::cout << "Factorial of " << n << " is: " << result << std::endl;
    return 0;
}
```
在这个示例中，定义了一个 constexpr 函数 factorial，它计算给定整数 n 的阶乘。这个函数在编译时进行计算，因为它的参数和返回值都是编译时常量。
在 main 函数中，声明了一个 constexpr 整数 n，然后使用 factorial 函数来计算 n 的阶乘，并将结果存储在 constexpr 整数 result 中。由于所有的操作都在编译时进行，因此 result 是一个编译时常量。
这个示例演示了如何使用 constexpr 来创建在编译时计算的常量表达式，以及如何在运行时使用这些常量值。