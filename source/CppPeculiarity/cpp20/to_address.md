```
#include <iostream>
#include <memory>
int main() {
    int a = 42;
    int* p = &a;
    std::shared_ptr<int> sp = std::make_shared<int>(42);
    std::cout << "Address of a: " << std::to_address(p) << '\n';
    std::cout << "Address of shared_ptr: " << std::to_address(sp.get()) << '\n';
    return 0;
}
```
std::to_address是C++20中引入的一个实用工具，它用于获取指针或者指针包装器所指向的对象的地址。
首先创建了一个整数变量a和一个指向它的指针p，然后创建了一个std::shared_ptr<int>。
然后，使用std::to_address来获取这些指针所指向的地址，并打印出来