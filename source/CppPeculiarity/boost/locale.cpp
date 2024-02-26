#include <iostream>
#include <boost/locale.hpp>

int main() {
    // 设置本地化环境为系统默认
    boost::locale::generator gen;
    std::locale loc = gen("");

    // 在本地化环境下输出一句问候语
    std::cout.imbue(loc);
    std::cout << boost::locale::translate("Hello, World!") << std::endl;

    // 使用本地化环境格式化日期和时间(版本问题 可能无法使用)
    // boost::locale::date_time now = boost::locale::date_time::now();
    // std::cout << boost::locale::as::date_time << now << std::endl;

    return 0;
}