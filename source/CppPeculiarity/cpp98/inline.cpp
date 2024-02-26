#include <iostream>
inline int add(int a, int b) {
    return a + b;
}
int main() {
    std::cout << "1 + 2 = " << add(1, 2) << std::endl;  // 输出：1 + 2 = 3
    return 0;
}