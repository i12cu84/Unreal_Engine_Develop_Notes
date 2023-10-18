Boost.Fiber：用于协程和Fiber的库，支持协程开发和多线程。
示例：使用boost::fibers创建一个简单的协程。

```cpp
#include <boost/fiber/all.hpp>
#include <iostream>

int main() {
    boost::fibers::fiber fib([]() {
        std::cout << "Fiber started." << std::endl;
    });

    fib.join();
    std::cout << "Fiber finished." << std::endl;
}
```