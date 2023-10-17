Boost.Test：用于C++单元测试的库。
示例：编写一个简单的Boost.Test单元测试。

```cpp
#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>

int add(int a, int b) {
    return a + b;
}

BOOST_AUTO_TEST_CASE(test_addition) {
    BOOST_CHECK_EQUAL(add(2, 3), 5);
}
```