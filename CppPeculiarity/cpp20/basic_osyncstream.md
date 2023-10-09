```
#include <iostream>
#include <string_view>
#include <syncstream>
#include <thread>
void worker(const int id, std::ostream &os)
{
    std::string_view block;
    switch (id)
    {
    default:
        [[fallthrough]];
    case 0:
        block = "██";
        break;
    case 1:
        block = "▓▓";
        break;
    case 2:
        block = "▒▒";
        break;
    case 3:
        block = "░░";
        break;
    }
    for (int i = 1; i <= 50; ++i)
        os << block << std::flush;
    os << std::endl;
}
int main()
{
    std::cout << "Synchronized output should not cause any interference:" << std::endl;
    {
        auto scout1 = std::osyncstream{std::cout};
        auto scout2 = std::osyncstream{std::cout};
        auto scout3 = std::osyncstream{std::cout};
        auto scout4 = std::osyncstream{std::cout};
        auto w1 = std::jthread{worker, 0, std::ref(scout1)};
        auto w2 = std::jthread{worker, 1, std::ref(scout2)};
        auto w3 = std::jthread{worker, 2, std::ref(scout3)};
        auto w4 = std::jthread{worker, 3, std::ref(scout4)};
    }
    std::cout << "\nLack of synchronization may cause some interference on output:" << std::endl;
    {
        auto w1 = std::jthread{worker, 0, std::ref(std::cout)};
        auto w2 = std::jthread{worker, 1, std::ref(std::cout)};
        auto w3 = std::jthread{worker, 2, std::ref(std::cout)};
        auto w4 = std::jthread{worker, 3, std::ref(std::cout)};
    }
    return 0;
}
```
std::basic_osyncstream是C++20中引入的一个类模板，它是std::basic_syncbuf的便利包装器。
它提供了一种机制来同步写入同一流的线程。

创建了四个名为scout1、scout2、scout3和scout4的std::osyncstream实例，它们都包装了std::cout。
然后我们创建了四个线程，它们都调用了函数 worker()。
在函数中，每个线程都向其对应的 std::osyncstream 实例写入数据。
由于 std::osyncstream 提供了同步机制，所以即使多个线程同时写入 std::cout，输出也不会出现干扰。