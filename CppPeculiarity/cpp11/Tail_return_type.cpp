// C++程序来说明C++ 11中的尾部返回类型
#include <iostream>

// 使用auto和decltype的尾部返回类型
auto add (int a, int b) -> decltype(a + b) {
    return a + b;
}

int main () {
    int x = 5, y = 10;
    auto result = add (x, y);
    std::cout << "Result: " << result << std::endl; // 输出：Result: 15
    return 0;
}