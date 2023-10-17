Boost.Fusion：用于元组和结构的库，可用于处理异构集合。
示例：创建一个异构元组并访问其成员。

```cpp
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/vector.hpp>
#include <iostream>
#include <string>

struct person {
    std::string name;
    int age;
};

BOOST_FUSION_ADAPT_STRUCT(person, (std::string, name)(int, age))

int main() {
    person p{"Alice", 30};
    std::cout << boost::fusion::at_c<0>(p) << ", " << boost::fusion::at_c<1>(p) << std::endl;
}
```