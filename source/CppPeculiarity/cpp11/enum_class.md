```
#include <iostream>
enum class Day
{
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};
int main()
{
    Day today = Day::Wednesday;
    // 直接打印今天是星期几，不需要使用 switch
    std::cout << "Today is " << static_cast<int>(today) + 1 << "th day of the week." << std::endl;
    return 0;
}
```
在这个示例中，声明了一个 Day 类型的变量 today，并将其赋值为 Day::Wednesday。然后，使用 static_cast 将 today 转换为整数，以获取星期几的索引，并打印相应的消息。
使用 enum class 的一个优点是，它可以提供更好的类型安全性，但仍然可以用相对简洁的方式表示枚举值。在这个示例中，直接将枚举值转换为整数来获取索引，以简化代码。