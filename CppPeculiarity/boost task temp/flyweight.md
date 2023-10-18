Boost.Flyweight：用于节省内存的库，适用于大量相似对象。
示例：使用飞行权重（Flyweight）优化字符串对象。

```cpp
#include <boost/flyweight.hpp>
#include <string>
#include <iostream>

int main() {
    typedef boost::flyweight<std::string> flystring;
    flystring a = "Hello";
    flystring b = "Hello";

    std::cout << "a and b are the same object: " << (a.get() == b.get()) << std::endl;
}
```