Boost.Compute：用于通用计算的库，支持GPU和多核CPU。
示例：在GPU上计算向量加法。

```cpp
#include <boost/compute/algorithm/inclusive_scan.hpp>
#include <boost/compute/container/vector.hpp>
#include <iostream>

int main() {
    namespace compute = boost::compute;
    compute::vector<int> input(1000);
    compute::vector<int> output(1000);

    for (int i = 0; i < 1000; i++) {
        input[i] = i;
    }

    compute::inclusive_scan(input.begin(), input.end(), output.begin());

    std::cout << "Result: ";
    for (int i = 0; i < 10; i++) {
        std::cout << output[i] << " ";
    }
    std::cout << "..." << std::endl;
}
```