照例
```
#include <iostream>
#include <thread>
#include <mutex>
std::once_flag flag;
void initializeOnce()
{
    auto fun = []()
    {
        std::cout << "Initialization is done." << std::endl;
    };
    std::call_once(flag, fun);
}
int main()
{
    // 创建多个线程，但只有一个线程会调用 fun
    std::thread t1(initializeOnce);
    std::thread t2(initializeOnce);
    t1.join();
    t2.join();
    return 0;
}
```
在这个示例中，定义了一个 std::once_flag 对象 flag 和一个函数 doInitialization，该函数包含需要执行一次的初始化操作。

然后，定义了一个名为 initializeOnce 的函数，该函数使用 std::call_once 来确保 doInitialization 函数只被调用一次。通过 std::call_once(flag, doInitialization)，告诉 C++ 运行时系统只有一个线程会调用 doInitialization，即使多个线程同时调用 initializeOnce。

最后，创建了多个线程 t1和t2 ，它们都调用 initializeOnce 函数。由于 std::call_once 的存在，doInitialization 函数只会在第一个线程中被调用，其他线程会等待直到初始化完成。

这个示例演示了如何使用 std::call_once 和 std::once_flag 来确保在多线程环境下某个函数只被调用一次。这在执行初始化或资源分配等操作时非常有用。