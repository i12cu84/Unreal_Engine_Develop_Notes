Boost.Timer：用于测量时间和性能的库，提供计时器功能。
示例：使用Boost.Timer测量代码执行时间。

```cpp
#include <boost/timer/timer.hpp>
#include <iostream>

int main() {
    boost::timer::cpu_timer timer;

    // Perform some time-consuming operation
    for (int i = 0; i < 1000000; ++i) {
        // ...
    }

    timer.stop();
    std::cout << "Elapsed time: " << timer.format() << std::endl;
}
```