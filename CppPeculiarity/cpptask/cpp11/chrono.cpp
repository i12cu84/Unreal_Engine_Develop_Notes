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
