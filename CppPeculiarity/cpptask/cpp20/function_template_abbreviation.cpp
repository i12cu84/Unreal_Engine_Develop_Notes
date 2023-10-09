#include <iostream>

// 使用函数模板缩写定义一个通用的加法函数
template<typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    int result = add(5, 3); // 可以省略模板参数类型的指定
    std::cout << "Result: " << result << std::endl;

    double result2 = add(3.14, 2.71); // 同样适用于其他类型
    std::cout << "Result2: " << result2 << std::endl;

    return 0;
}