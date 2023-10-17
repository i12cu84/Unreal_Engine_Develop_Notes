Boost.Histogram2：用于直方图操作的库，支持多维直方图和数据分析。
示例：使用boost::histogram2创建多维直方图并分析数据分布。

```cpp
#include <boost/histogram2/histogram.hpp>
#include <iostream>

int main() {
    using namespace boost::histogram2;

    auto h = make_histogram(axis::regular<>(10, -1.0, 1.0), axis::regular<>(5, 0.0, 1.0));
    h(0.2, 0.5);

    for (const auto& bin : indexed(h)) {
        std::cout << "Bin " << bin.index() << " has count " << bin.value() << std::endl;
    }
}
```