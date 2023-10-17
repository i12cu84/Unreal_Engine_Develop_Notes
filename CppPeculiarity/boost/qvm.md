Boost.QVM：用于矢量和矩阵数学的库，支持矢量和矩阵操作。
示例：使用boost::qvm进行矢量点积运算。

```cpp
#include <boost/qvm/vec.hpp>
#include <iostream>

int main() {
    typedef boost::qvm::vec<float, 3> Vec3;
    Vec3 v1 = {1.0f, 2.0f, 3.0f};
    Vec3 v2 = {4.0f, 5.0f, 6.0f};

    float dot_product = boost::qvm::dot(v1, v2);
    std::cout << "Dot product of vectors: " << dot_product << std::endl;
}
```