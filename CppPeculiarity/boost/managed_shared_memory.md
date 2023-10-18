Boost.Interprocess Shared Memory：使用Boost.Interprocess进行共享内存通信的示例。

```cpp
#include <boost/interprocess/managed_shared_memory.hpp>
#include <iostream>

int main() {
    using namespace boost::interprocess;

    managed_shared_memory segment(create_only, "MySharedMemory", 65536);
    int* integer = segment.construct<int>("MyInteger")(42);

    std::cout << "Shared integer: " << *integer << std::endl;
}
```