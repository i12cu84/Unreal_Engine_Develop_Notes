```
#include <iostream>
#include <string>
int main()
{
    std::string s = "Hello, World!";
    // 检查字符串是否以特定的前缀开始
    if (s.starts_with("Hello"))
        std::cout << "The string starts with 'Hello'\n";
    // 检查字符串是否以特定的后缀结束
    if (s.ends_with("World!"))
        std::cout << "The string ends with 'World!'\n";
    return 0;
}
```
C++20为std::string和std::string_view添加了starts_with和ends_with成员函数。
这些函数可以用来检查一个字符串是否以特定的前缀开始或以特定的后缀结束。

首先创建了一个字符串s。
然后，我们使用starts_with函数来检查s是否以"Hello"开始，
如果是，我们就打印一条消息。
接着，我们使用ends_with函数来检查s是否以"World!"结束，如果是，我们就打印一条消息。