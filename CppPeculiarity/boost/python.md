Boost.Python：用于将C++代码与Python集成的库。
示例：使用Boost.Python创建一个C++模块供Python调用。

```cpp
#include <boost/python.hpp>

int add(int a, int b) {
    return a + b;
}

BOOST_PYTHON_MODULE(example) {
    using namespace boost::python;
    def("add", add);
}
```