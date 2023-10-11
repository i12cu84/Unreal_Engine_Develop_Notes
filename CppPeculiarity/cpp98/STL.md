**STL库**：C++98引入了标准模板库（STL），它包含了一系列模板类和函数，用于处理常见的数据结构和算法¹。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {3, 1, 4, 1, 5, 9};
    std::sort(v.begin(), v.end());

    for (int i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
```