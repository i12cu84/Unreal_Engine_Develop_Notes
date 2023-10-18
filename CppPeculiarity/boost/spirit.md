Boost.Spirit：提供了一种用于解析和生成文本的库，支持自定义语法和语义。以下是一个简单的Boost.Spirit程序示例，它解析了一个简单的表达式并计算其值：

```
#include <iostream>
#include <string>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

int main()
{
    std::string input = "1 + 2 * 3";
    int result;

    auto it = input.begin();
    qi::phrase_parse(it, input.end(),
                     qi::int_ >> *(('+' >> qi::int_) | ('*' >> qi::int_)),
                     qi::space, result);

    std::cout << "result = " << result << "\n";

    return 0;
}
```