Boost.Multiprecision：用于高精度数学计算的库，支持大整数和多重精度浮点数。
示例：使用boost::multiprecision计算大整数的阶乘。

```cpp
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

int main() {
    using namespace boost::multiprecision;

    cpp_int factorial = 1;
    int n = 100;  // Calculate 100!

    for (int i = 1; i <= n; ++i) {
        factorial *= i;
    }

    std::cout << "100! = " << factorial << std::endl;
}
```