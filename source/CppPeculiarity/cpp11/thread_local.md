照例
```
#include <iostream>
#include <thread>
thread_local int threadLocalValue = 0;
int threadCommonValue = 0;
void threadFunction()
{
    // 在每个线程中修改 Value
    threadLocalValue++;
    threadCommonValue++;
    std::cout << "Thread Local Value: " << threadLocalValue << std::endl;
    std::cout << "Thread Common Value: " << threadCommonValue << std::endl;
}
int main()
{
    // 创建多个线程，并在每个线程中执行 threadFunction
    std::thread t1(threadFunction);
    std::thread t2(threadFunction);
    t1.join();
    t2.join();
    return 0;
}
```

这段代码演示了多线程环境中的两种不同类型的变量：thread_local 变量和普通变量。
threadLocalValue 是一个 thread_local 整数变量，每个线程都有自己的副本。在 threadFunction 函数中，每个线程都会递增它自己的 threadLocalValue，因此每个线程都有不同的值。最后，通过 std::cout 打印出每个线程的 threadLocalValue 值。
threadCommonValue 是一个普通整数变量，多个线程共享同一个变量。在 threadFunction 函数中，所有线程都递增同一个 threadCommonValue 变量，因此它是一个全局变量，所有线程都对它有影响。最后，通过 std::cout 打印出每个线程的 threadCommonValue 值。
当运行程序时，可能会看到如下输出：
Thread Local Value: 1
Thread Local Value: 1
Thread Common Value: 1
Thread Common Value: 2
这个示例展示了 thread_local 变量和普通变量之间的区别。thread_local 变量每个线程都有自己的副本，互不干扰，而普通变量是全局共享的，多个线程可以同时访问和修改它，需要小心线程同步问题。