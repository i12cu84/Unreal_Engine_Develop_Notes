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
