#include <iostream>

// 使用 __attribute__ 告诉编译器对这个函数进行优化
int __attribute__((optimize("O2"))) add(int a, int b) {
    return a + b;
}

int main() {
    int result = add(3, 4);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
