#include <atomic>
#include <memory>
#include <iostream>
int main()
{
    // 使用std::atomic<std::shared_ptr>
    std::atomic<std::shared_ptr<int>> ptr = std::make_shared<int>(10);
    auto newPtr = std::make_shared<int>(20);
    ptr.store(newPtr, std::memory_order_release);
    std::shared_ptr<int> expected = ptr.load(std::memory_order_acquire);
    if (expected != nullptr)
        std::cout << "New value: " << *expected << std::endl;

    // 使用std::atomic<float>
    std::atomic<float> num(10.0f);
    float newValue = 20.0f;
    num.store(newValue, std::memory_order_release);
    float expectedNum = num.load(std::memory_order_acquire);
    std::cout << "New value: " << expectedNum << std::endl;

    return 0;
}
/*
新增atomic<std::shared_ptr>和atomic<float>
*/