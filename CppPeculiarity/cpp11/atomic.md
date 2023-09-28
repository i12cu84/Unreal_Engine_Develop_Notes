在 C++ 中，可以使用标准库的 std::atomic 类来执行原子操作。

下面是一个示例，演示如何使用 std::atomic 来执行一个简单的原子计数操作：
```
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> counter(0);

void incrementCounter() {
    for (int i = 0; i < 10000; ++i) {
        counter.fetch_add(1, std::memory_order_relaxed);
    }
}

int main() {
    const int numThreads = 4;
    std::thread threads[numThreads];

    // 创建多个线程，每个线程都会增加计数器的值
    for (int i = 0; i < numThreads; ++i) {
        threads[i] = std::thread(incrementCounter);
    }

    // 等待所有线程完成
    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
    }

    // 输出最终的计数器值
    std::cout << "Final counter value: " << counter.load(std::memory_order_relaxed) << std::endl;

    return 0;
}
```
在这个示例中，使用 std::atomic<int> 来声明一个原子整数变量 counter，初始值为 0。

然后，创建了多个线程，每个线程都会调用 incrementCounter 函数，该函数会对 counter 执行原子的自增操作。

注意以下关键点：

1.使用 fetch_add 函数来执行自增操作，它是一个原子操作。在这个示例中，使用了 std::memory_order_relaxed 内存顺序，它表示对内存的松散访问控制，适用于这种简单的场景。可以根据需要选择其他内存顺序。

2.创建了多个线程来同时增加计数器的值，因此需要确保原子性，以避免竞态条件。std::atomic 提供了这种保证。

3.等待所有线程完成，并输出最终的计数器值。由于原子操作的使用，计数器的值应该是正确的，不会发生竞态条件。