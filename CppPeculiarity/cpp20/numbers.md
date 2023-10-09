C++20 引入了一个新的头文件 `<numbers>`，其中包含了一些常用的数学常量，如下所示：

| 常量名称 | 常量值 |
|----------|--------|
| `std::numbers::e_v` | 自然对数的底数 e |
| `std::numbers::log2e_v` | 以 2 为底的 e 的对数 |
| `std::numbers::log10e_v` | 以 10 为底的 e 的对数 |
| `std::numbers::pi_v` | 圆周率 π |
| `std::numbers::inv_pi_v` | π 的倒数 |
| `std::numbers::inv_sqrtpi_v` | π 的平方根的倒数 |
| `std::numbers::ln2_v` | 自然对数 2 的值 |
| `std::numbers::ln10_v` | 自然对数 10 的值 |
| `std::numbers::sqrt2_v` | 2 的平方根 |
| `std::numbers::sqrt3_v` | 3 的平方根 |
| `std::numbers::inv_sqrt3_v` | 3 的平方根的倒数 |

这些常量都是编译期常量，可以在模板参数中使用。例如：

```c++
#include <iostream>
#include <numbers>

int main() {
    std::cout << "π ≈ " << std::numbers::pi_v<double> << std::endl;
    return 0;
}
```

输出结果为：

```
π ≈ 3.14159
```
