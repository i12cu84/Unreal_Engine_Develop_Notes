Boost.LexicalCast：用于类型转换的库，支持不同类型之间的转换。
示例：使用boost::lexical_cast执行类型转换。

```cpp
#include <boost/lexical_cast.hpp>
#include <iostream>

int main() {
    try {
        std::string str_value = "42";
        int int_value = boost::lexical_cast<int>(str_value);
        std::cout << "Converted int value: " << int_value << std::endl;
    } catch (const boost::bad_lexical_cast& e) {
        std::cerr << "Conversion error: " << e.what() << std::endl;
    }
}
```