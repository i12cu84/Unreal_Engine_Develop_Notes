```
#include <iostream>
#include <functional>
void print_sum(int a, int b)
{
    std::cout << a + b << '\n';
}
int main()
{
    auto print_plus_10 = std::bind_front(print_sum, 10);
    print_plus_10(5); // 输出15
    return 0;
}
```
std::bind_front是C++20中引入的一个函数模板，它用于创建一个新的可调用对象，该对象将一些参数绑定到给定的函数或可调用对象的前面。
这意味着，当你调用返回的可调用对象时，这些绑定的参数将作为原始函数的前几个参数。

首先定义了一个名为print_sum的函数，它接受两个整数参数并打印它们的和。
然后，使用std::bind_front(print_sum, 10)来创建一个新的可调用对象print_plus_10。
当调用print_plus_10(5)时，它实际上是在调用print_sum(10, 5)。