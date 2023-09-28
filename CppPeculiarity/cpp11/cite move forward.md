先贴代码
```
#include <iostream>
#include <utility>
// 左值引用函数
void lvalueFunction(int &x)
{
    std::cout << "Received an lvalue: " << x << std::endl;
}
// 右值引用函数
void rvalueFunction(int &&x)
{
    std::cout << "Received an rvalue: " << x << std::endl;
}
// 使用移动语义的函数
void moveFunction(int &&x)
{
    int y = std::move(x); // 使用 std::move 将右值引用转换为左值引用
    std::cout << "Moved value: " << y << std::endl;
}
// 左值引用函数(用于完美转发)
void forwardOutput(int &x)
{
    std::cout << "Received an lvalue: " << x << std::endl;
}
// 右值引用函数(用于完美转发)
void forwardOutput(int &&x)
{
    std::cout << "Received an rvalue: " << x << std::endl;
}
// 完美转发函数
template <typename T>
void forwardFunction(T &&x)
{
    forwardOutput(std::forward<T>(x)); // 使用 std::forward 完美转发
}
int main()
{
    int a = 42;
    // 左值引用
    lvalueFunction(a);
    // 右值引用
    rvalueFunction(7);
    // 移动语义
    int b = 100;
    moveFunction(std::move(b));
    // 完美转发
    int c = 200;
    forwardFunction(c);   // 传递左值
    forwardFunction(300); // 传递右值
    return 0;
}
```
lvalueFunction 接受一个左值引用，它可以处理普通变量（左值）。

rvalueFunction 接受一个右值引用，它可以处理临时值（右值）。

moveFunction 使用了移动语义，将一个右值引用的值移动到一个新变量中，然后输出移动后的值。

forwardFunction 是一个模板函数，使用了完美转发（perfect forwarding）技术。它接受一个通用引用 T&& 并使用 std::forward 来根据传递的参数类型正确地将参数转发给 lvalueFunction。