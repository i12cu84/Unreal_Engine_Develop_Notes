#include <iostream>
#include <optional>
// 检查编译器是否支持__has_include宏
#if defined __has_include
// 检查是否存在<charconv>头文件
    #if __has_include(<charconv>)
        // 如果存在<charconv>头文件，定义has_charconv宏并包含<charconv>头文件
        #define has_charconv 1
        #include <charconv>
    #endif
#endif
// 定义一个函数，将输入字符串转换为整数
std::optional<int> ConvertToInt(const std::string& str) {
    int value{}; // 初始化整数值为0
    #ifdef has_charconv // 如果已经定义了has_charconv宏
        // 计算指向字符串末尾的指针
        const auto last = str.data() + str.size();
        // 使用std::from_chars函数进行转换
        const auto res = std::from_chars(str.data(), last, value);
        // 如果转换成功且转换结束指针等于字符串末尾，返回整数值
        if (res.ec == std::errc{} && res.ptr == last)
        {
            return value;
        }
    #else // 如果没有定义has_charconv宏
        // 这里可以实现备选的转换方式，例如使用其他函数或库进行转换
        // 如果没有定义has_charconv宏，这个部分的代码会被使用
    #endif
        // 如果无法转换或备选方法失败，返回std::nullopt表示没有结果
        return std::nullopt;
}
int main()
{
    return 0;
}