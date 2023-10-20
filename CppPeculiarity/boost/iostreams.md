Boost.Iostreams：用于扩展I/O流操作的库，支持自定义数据源和数据目标。
示例：使用boost::iostreams实现一个自定义数据源。
注意:需要链路库
```cpp
#include <boost/iostreams/device/mapped_file.hpp>
#include <iostream>

int main() {
    boost::iostreams::mapped_file_source file("..\\README.md");

    if (file.is_open()) {
        std::cout << "File size: " << file.size() << " bytes" << std::endl;
        std::cout.write(file.data(), file.size());
    }
}
```