```
#include <iostream>
int main() {
    volatile int x = 10; // 使用 volatile 声明一个整数变量
    std::cout << "Initial value of x: " << x << std::endl;
    // 模拟外部因素改变 x 的值
    int* ptr = const_cast<int*>(&x);
    *ptr = 20;
    std::cout << "Modified value of x: " << x << std::endl;
    return 0;
}
```
在这个示例中，声明了一个 volatile 整数变量 x。然后，通过 const_cast 将 x 的地址转换为非 volatile 指针，以模拟外部因素（例如硬件）改变了 x 的值。在这种情况下，编译器不会对 x 的访问进行优化，以确保每次访问都会从内存中读取最新的值。

请注意，尽管 volatile 可以确保每次访问都会从内存中读取最新的值，但它并不提供线程安全性，因此在多线程编程中通常不是解决竞态条件或数据竞争的最佳选择。更好的方法是使用线程同步工具，如 std::mutex 和 std::atomic，来确保多个线程安全地访问和修改共享变量。