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
