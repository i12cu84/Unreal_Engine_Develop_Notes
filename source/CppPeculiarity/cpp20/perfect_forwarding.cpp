#include <iostream>
#include <utility>

template<typename... Args>
auto sum(Args&&... args) {
    return (args + ...);
}

int main() {
    int a = 1, b = 2, c = 3;
    auto result = sum(a, b, c);
    std::cout << result << std::endl; // 输出 6
    return 0;
}