Boost.Rational：用于有理数操作的库，支持有理数的计算和表示。
示例：使用boost::rational执行有理数运算。

```cpp
#include <boost/rational.hpp>
#include <iostream>

int main() {
    boost::rational<int> r1(1, 2);
    boost::rational<int> r2(3, 4);

    boost::rational<int> result = r1 + r2;

    std::cout << "Result of addition: " << result << std::endl;
}
```