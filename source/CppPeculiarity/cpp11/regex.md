照例
```
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
```

在这个示例中，首先定义了一个包含文本的字符串 text，然后创建了一个正则表达式模式 emailRegex，用于匹配电子邮件地址。这个模式可以匹配常见的电子邮件地址格式。
接下来，使用 std::sregex_iterator 来遍历文本中所有匹配的电子邮件地址。std::sregex_iterator 接受三个参数：输入字符串的开始迭代器、结束迭代器和正则表达式模式。将其与结束迭代器 end 进行比较，以遍历所有匹配项。
对于每个匹配项，将其保存在 std::smatch 对象中，并打印出匹配的电子邮件地址。
运行此示例，它将查找并输出文本中的所有电子邮件地址。这是一个简单的示例，演示了如何使用 C++11 的正则表达式库进行文本匹配。



另外...


C++11 引入的正则表达式库（<regex> 头文件）允许你在 C++ 中进行正则表达式匹配。正则表达式是一种强大的文本匹配工具，用于搜索、提取和替换文本中的模式。以下是一些 C++11 正则表达式的基本用法规则：

包含头文件：要使用正则表达式库，首先包含 <regex> 头文件。

#include <regex>

定义正则表达式模式：使用 std::regex 类来定义正则表达式模式。正则表达式模式是一个字符串，描述了要匹配的文本模式。

std::regex pattern("your_regex_pattern_here");

使用std::smatch或std::cmatch对象来存储匹配结果：std::smatch 用于匹配 std::string 类型的字符串，而 std::cmatch 用于匹配 const char* 类型的字符串。匹配结果将存储在这些对象中。

std::smatch match; // 用于匹配 std::string

执行正则匹配：使用 std::regex_search 函数来执行正则匹配。这个函数接受要匹配的字符串、匹配结果存储对象和正则表达式模式。

std::string text = "your_text_here";
if (std::regex_search(text, match, pattern)) {
    // 匹配成功
}

遍历匹配结果：如果匹配成功，你可以遍历匹配结果。匹配结果存储在 std::smatch 对象中，可以通过索引或迭代器来访问。

for (size_t i = 0; i < match.size(); ++i) {
    std::cout << "Match " << i << ": " << match[i] << std::endl;
}

正则表达式选项：可以使用正则表达式选项来指定匹配的行为，例如大小写敏感或不敏感、单行模式等。可以使用 std::regex_constants 中定义的常量来设置选项。

std::regex pattern("pattern", std::regex_constants::flag);

捕获分组：正则表达式可以包含捕获分组，允许你提取匹配的部分文本。捕获分组用小括号 ( ) 定义。

std::regex pattern("(\\d+)-(\\d+)");

替换文本：使用 std::regex_replace 函数来替换匹配的文本。

std::string replaced = std::regex_replace(text, pattern, "replacement_text");