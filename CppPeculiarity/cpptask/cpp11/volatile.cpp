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
