Boost.Endian：用于处理不同字节顺序的库，可用于网络编程和文件I/O。
示例：将整数从本机字节顺序转换为网络字节顺序。

```cpp
#include <boost/endian/conversion.hpp>
#include <iostream>

int main() {
    int nativeValue = 12345;
    int networkValue = boost::endian::native_to_big(nativeValue);

    std::cout << "Native Value: " << nativeValue << std::endl;
    std::cout << "Network Value: " << networkValue << std::endl;
}
```