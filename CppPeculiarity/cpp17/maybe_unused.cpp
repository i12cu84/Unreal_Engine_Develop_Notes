#include <iostream>
[[maybe_unused]] void unusedFunction()
{
    std::cout << "This function may not be used." << std::endl; // 这个函数被声明为可能未使用
}
int main()
{
    [[maybe_unused]] int y = 10; // 变量 y 被声明为可能未使用
    return 0;
}
