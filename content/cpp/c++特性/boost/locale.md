Boost.Locale：用于本地化和国际化的库。
示例：将日期时间格式化为不同语言。
注意:记得加上链路库
```cpp
#include <iostream>
#include <boost/locale.hpp>

int main() {
    // 设置本地化环境为系统默认
    boost::locale::generator gen;
    std::locale loc = gen("");

    // 在本地化环境下输出一句问候语
    std::cout.imbue(loc);
    std::cout << boost::locale::translate("Hello, World!") << std::endl;

    // 使用本地化环境格式化日期和时间
    // boost::locale::date_time now = boost::locale::date_time::now();
    // std::cout << boost::locale::as::date_time << now << std::endl;

    return 0;
}
```
