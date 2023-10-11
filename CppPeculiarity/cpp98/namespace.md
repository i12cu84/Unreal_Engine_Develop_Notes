**命名空间**：C++98支持命名空间，这有助于防止命名冲突¹。

```cpp
#include <iostream>

namespace my_namespace {
    int var = 10;
}

int main() {
    std::cout << my_namespace::var << std::endl;

    return 0;
}
```