```
#include <iostream>
#include <chrono>
int main() {
    auto start = std::chrono::steady_clock::now();// 获取当前时间点
    for (int i = 0; i < 1000000; ++i); // 做一些耗时的操作（模拟）    
    auto end = std::chrono::steady_clock::now();// 获取当前时间点
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);// 计算耗时
    std::cout << "Time elapsed: " << duration.count() << " milliseconds" << std::endl;// 打印耗时
    return 0;
}
```
在这个示例中，使用了 <chrono> 头文件中的类型和时钟：
std::chrono::steady_clock 是一个稳定时钟，用于测量时间点，通常用于性能测量。
std::chrono::time_point 表示一个时间点，使用它来获取当前时间点 start 和 end。
std::chrono::duration 表示时间的持续时间，使用 std::chrono::duration_cast 来计算 start 到 end 之间的持续时间。
在示例中，获取 start 时间点，执行一些模拟的计算操作，然后获取 end 时间点。接着，计算持续时间并将其以毫秒为单位打印出来，以测量这些计算操作的耗时。
这个示例演示了如何使用 <chrono> 头文件中的类型和时钟来测量代码的执行时间。这对于性能分析和优化是非常有用的。