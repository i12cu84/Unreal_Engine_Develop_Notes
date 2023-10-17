Boost.Math：用于数学和数值计算的库，提供了数学函数和特殊数学常数。
示例：计算圆周率（π）的近似值。

```cpp
#include <boost/math/constants/constants.hpp>
#include <iostream>

int main() {
    double pi = boost::math::constants::pi<double>();
    std::cout << "Approximate value of pi: " << pi << std::endl;
}
```