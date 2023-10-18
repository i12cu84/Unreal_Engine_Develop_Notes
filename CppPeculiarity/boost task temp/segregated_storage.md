Boost.SegregatedStorage：用于存储和访问多种类型对象的库。
示例：使用boost::segregated_storage存储多种类型对象。

```
cpp
#include <boost/segregated_storage.hpp>
#include <iostream>

struct WidgetA {
    int value;
};

struct WidgetB {
    double value;
};

int main() {
    boost::segregated_storage storage;
    auto ptr1 = storage.construct<WidgetA>(42);
    auto ptr2 = storage.construct<WidgetB>(3.14);

    std::cout << "WidgetA value: " << ptr1->value << std::endl;
    std::cout << "WidgetB value: " << ptr2->value << std::endl;
}
```