Boost.Stacktrace：用于获取程序堆栈跟踪信息的库。
示例：在程序中获取堆栈跟踪信息。

```cpp
#include <boost/stacktrace.hpp>
#include <iostream>

void printStackTrace() {
    boost::stacktrace::stacktrace st;
    std::cout << st << std::endl;
}

int main() {
    printStackTrace();
}
```