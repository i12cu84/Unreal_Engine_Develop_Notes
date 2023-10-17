#include <iostream>
#include <regex>
#include <string>
int main() {
    std::string text = "Hello, my email is i12cu84@foxmail.com and another email is i12cu84@foxmail.org.";
    // 定义一个正则表达式模式，匹配电子邮件地址
    std::regex emailRegex(R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,4}\b)");
    // 使用 std::sregex_iterator 遍历所有匹配的电子邮件地址
    std::sregex_iterator emailMatches(text.begin(), text.end(), emailRegex);
    std::sregex_iterator end;
    while (emailMatches != end) {
        std::smatch match = *emailMatches;
        std::cout << "Found email: " << match.str() << std::endl;
        ++emailMatches;
    }
    return 0;
}