#include <iostream>
#include <charconv>
#include <cstring>
int main()
{
    // 使用 std::to_chars 将整数转换为字符串
    int intValue = 42;
    char buffer[20]; // 定义足够大的字符数组来存储结果
    auto result = std::to_chars(buffer, buffer + sizeof(buffer), intValue);
    std::cout << "Converted to string: " << buffer << std::endl;
    
    // 使用 std::from_chars 将字符串转换为整数
    const char *str = "12345";
    int parsedValue;
    auto [ptr, ec] = std::from_chars(str, str + strlen(str), parsedValue);
    std::cout << "Parsed integer: " << parsedValue << std::endl;
    return 0;
}
