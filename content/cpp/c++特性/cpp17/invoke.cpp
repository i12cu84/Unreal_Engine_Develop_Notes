#include <iostream>
#include <functional>

void func(int num) {
    std::cout << "Number: " << num << std::endl;
}

int main() {
    std::invoke(func, 5);
    return 0;
}