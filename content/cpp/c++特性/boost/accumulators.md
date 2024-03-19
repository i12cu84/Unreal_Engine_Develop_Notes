Boost.Accumulators：用于统计和数据收集的库。
示例：计算一组数据的均值和标准差。

```cpp
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <iostream>

int main() {
    using namespace boost::accumulators;
    accumulator_set<double, stats<tag::mean, tag::variance>> acc;

    acc(1.1);
    acc(2.2);
    acc(3.3);

    std::cout << "Mean: " << mean(acc) << std::endl;
    std::cout << "Variance: " << variance(acc) << std::endl;
}
```