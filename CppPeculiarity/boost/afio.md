Boost.AFIO：用于文件I/O操作的库，支持异步文件操作。
示例：使用Boost.AFIO进行异步文件读取。

```cpp
#include <boost/afio.hpp>
#include <iostream>

int main() {
    boost::afio::async_file file("example.txt", boost::afio::file_flags::read);
    boost::afio::file_handle::const_buffer_type buffer(1024);

    file.read(buffer).get();
    std::cout << "Read: " << buffer.data() << std::endl;
}
```