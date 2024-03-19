Boost.Optional：用于安全地表示可能为空的值的库。
示例：使用boost::optional表示可能为空的整数。

```cpp
#include <boost/optional.hpp>
#include <iostream>

int main() {
    boost::optional<int> maybeValue;
    if (maybeValue) {
        std::cout << "Value is present: " << *maybeValue << std::endl;
    } else {
        std::cout << "Value is empty." << std::endl;
    }

    maybeValue = 42;
    if (maybeValue) {
        std::cout << "Value is present: " << *maybeValue << std::endl;
    }
}
```