#include <chrono>
#include <iostream>
#include <format>
int main()
{
    using namespace std::chrono;
    // 获取当前的系统时间
    auto now = system_clock::now();

    // 创建一个时区
    auto tz = locate_zone("Asia/Shanghai");
    zoned_time zt{tz, now};
    std::cout << zt << '\n';

    // 转换为日历时间
    auto now_time_t = system_clock::to_time_t(now);
    std::cout << "Current time: " << ctime(&now_time_t);
    return 0;
}
/*
chrono库新增时区与日历功能
另外，locate_zone的参数可以用：
    “Asia/Shanghai”：北京上海时区
    “Asia/Tokyo”：东京的时区
    “America/New_York”：纽约的时区
    “Europe/Paris”：巴黎的时区
    “Australia/Sydney”：悉尼的时区
    “Africa/Johannesburg”：约翰内斯堡的时区
*/
