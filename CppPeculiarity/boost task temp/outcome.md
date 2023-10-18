Boost.Outcome：用于处理操作结果和错误的库。
示例：使用boost::outcome来处理可能失败的操作。

```cpp
#include <boost/outcome.hpp>
#include <iostream>

BOOST_OUTCOME_AUTO my_operation(int value) {
    if (value < 0) {
        return boost::outcome_v2::failure(std::error_code(42, std::generic_category()));
    }
    return value * 2;
}

int main() {
    auto result = my_operation(5);
    if (result) {
        std::cout << "Success: " << result.value() << std::endl;
    } else {
        std::cout << "Error: " << result.error().message() << std::endl;
    }
}
```