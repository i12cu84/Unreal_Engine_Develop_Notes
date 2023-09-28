照例,先贴代码
```
#include <iostream>
#include <functional>
// 一个简单的函数
int add(int a, int b)
{
    return a + b;
}
int main()
{
    // 使用 std::function 来存储可调用对象
    std::function<int(int, int)> func;
    // 使用 std::bind 创建一个可调用对象,std::placeholders为c++标准库占位符
    auto bindAdd = std::bind(add, std::placeholders::_1, std::placeholders::_2);
    func = bindAdd;
    int result1 = func(3, 4);
    std::cout << "Result (using std::bind): " << result1 << std::endl;
    // 使用 Lambda 表达式创建一个可调用对象
    auto lambdaMultiply = [](int x, int y)
    {
        return x * y;
    };
    func = lambdaMultiply;
    int result2 = func(3, 4);
    std::cout << "Result (using Lambda): " << result2 << std::endl;
    return 0;
}
```
首先创建一个 std::function 对象 func，它可以存储可调用对象，接受两个整数参数并返回整数。

然后，使用 std::bind 创建了一个可调用对象 bindAdd，它将 add 函数绑定到前两个参数，并留下两个占位符 std::placeholders::_1 和 std::placeholders::_2 来表示参数位置。将 bindAdd 赋值给 func，然后使用 func 调用它来执行加法操作。

接下来，使用 Lambda 表达式创建了一个可调用对象 lambdaMultiply，它执行两个整数的乘法操作。将 lambdaMultiply 赋值给 func，并再次使用 func 来执行操作，这次是乘法操作。

这个示例演示了如何使用 std::function 存储不同的可调用对象，包括使用 std::bind 和 Lambda 表达式创建的可调用对象。std::function 允许在运行时动态切换可调用对象，从而实现更大的灵活性。

另，

lambda表达式允许捕获一定范围内的变量：

[]不捕获任何变量

[&]引用捕获，捕获外部作用域所有变量，在函数体内当作引用使用

[=]值捕获，捕获外部作用域所有变量，在函数内内有个副本使用

[=, &a]值捕获外部作用域所有变量，按引用捕获a变量

[a]只值捕获a变量，不捕获其它变量

另，当需要对捕获值进行修改时(修改外部值)需要加入关键字mutable即可，因为原有operator()是const类型

int a = 0;
auto fun = [=]() mutable { return a++; };