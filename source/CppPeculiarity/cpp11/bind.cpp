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
