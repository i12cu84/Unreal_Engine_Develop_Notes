Boost.SIMD：用于单指令多数据（SIMD）向量化操作的库。
示例：使用Boost.SIMD进行向量化操作。

```cpp
#include <boost/simd/pack.hpp>
#include <iostream>

int main() {
    boost::simd::pack<float, 4> a{1.0f, 2.0f, 3.0f, 4.0f};
    boost::simd::pack<float, 4> b{2.0f, 2.0f, 2.0f, 2.0f};
    boost::simd::pack<float, 4> result = a + b;

    for (int i = 0; i < 4; ++i) {
        std::cout << "Result[" << i << "] = " << result[i] << std::endl;
    }
}
```