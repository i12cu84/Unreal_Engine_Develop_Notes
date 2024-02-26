```
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
```
提示编译器修饰的内容可能暂时没有使用，避免产生警告