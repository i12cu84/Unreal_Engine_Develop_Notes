```
#include <format>
#include <iostream>
int main()
{
    int a = 3;
    double b = 4.5;
    std::string s = std::format("The sum of {} and {} is {}", a, b, a + b);
    std::cout << s << std::endl;
    return 0;
}
```
C++0中的std::format是一个非常强大的工具，它提供了一种类型安全且易于阅读的字符串格式化方法。以下是一些主要的特性：
替换字段：std::format使用花括号 {} 作为替换字段的占位符。这些替换字段在格式化时会被相应的参数值替换。
格式规范：std::format支持在替换字段内部定义格式规范，例如指定输出宽度、对齐方式和填充字符等。格式规范使用冒号 : 分隔，放在花括号内。
编译时类型检查：std::format在编译期间检查参数类型的正确性，以提高类型安全性。
自定义类型支持：std::format可以通过重载 formatter 特化来支持自定义类型的格式化。
性能优化：std::format在设计时充分考虑了性能问题，因此在许多场景下性能优于 iostreams。
    而与 printf 相比， std::format 的性能表现也非常出色。
总的来说，std::format提供了一种统一的、类型安全的、易于阅读和理解的方式来进行字符串格式化，使得代码更加简洁和高效。