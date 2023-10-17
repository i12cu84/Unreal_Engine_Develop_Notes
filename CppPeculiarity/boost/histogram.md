Boost.Histogram：用于直方图操作的库，支持数据分布分析。
示例：使用boost::histogram创建直方图并分析数据分布。

```cpp
#include <boost/histogram.hpp>
#include <iostream>

int main() {
    using namespace boost::histogram;

    auto h = make_histogram(axis::regular<>(10, -1.0, 1.0));
    h.fill(0.2);

    for (const auto& bin : indexed(h)) {
        std::cout << "Bin " << bin.index() << " has count " << bin.value() << std::endl;
    }
}
```