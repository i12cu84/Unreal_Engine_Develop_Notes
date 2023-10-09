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
    for (int i = 0; i < numThreads; ++i) 
        threads[i] = std::thread(incrementCounter);
    for (int i = 0; i < numThreads; ++i) 
        threads[i].join();    
    std::cout << "Final counter value: " << counter.load(std::memory_order_relaxed) << std::endl;
    return 0;
}
