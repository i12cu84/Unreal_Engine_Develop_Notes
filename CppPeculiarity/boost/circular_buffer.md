Boost.CircularBuffer：用于循环缓冲区的库，支持高效的环形数据存储。
示例：使用boost::circular_buffer来实现一个循环队列。

```cpp
#include <boost/circular_buffer.hpp>
#include <iostream>

int main() {
    boost::circular_buffer<int> buffer(5);
    buffer.push_back(1);
    buffer.push_back(2);
    buffer.push_back(3);

    for (int value : buffer) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    buffer.push_back(4);
    buffer.push_back(5);

    for (int value : buffer) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}
```