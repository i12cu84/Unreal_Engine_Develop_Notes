Boost.Bimap：用于双射（bidirectional map）的库，允许快速双向查找。
示例：创建一个双射并进行双向查找。

```cpp
#include <boost/bimap.hpp>
#include <iostream>

int main() {
    using namespace boost::bimaps;

    bimap<int, std::string> bm;
    bm.insert({1, "one"});
    bm.insert({2, "two"});

    std::cout << "Value for key 1: " << bm.by<left>(1) << std::endl;
    std::cout << "Key for value 'two': " << bm.by<right>("two") << std::endl;
}
```