Boost.TypeIndex：用于类型信息的库，支持运行时类型信息查询。
示例：使用boost::typeindex查询类型信息。

```cpp
#include <boost/type_index.hpp>
#include <iostream>

int main() {
    int value = 42;
    std::cout << "Type of value: " << boost::typeindex::type_id_runtime(value).pretty_name() << std::endl;
}
```