```
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
```
C++20 引入了“函数模板缩写”（Function Template Abbreviation）特性，可以简化模板函数的定义和调用。

在上述代码中，使用函数模板缩写定义了一个通用的加法函数 `add`，它可以接受两个相同类型的参数并返回它们的和。在 `main` 函数中，可以直接调用 `add` 函数而无需显式指定模板参数的类型，编译器会根据传入的参数推断出正确的类型。
注意：虽然函数模板缩写提供了便利性，减少了模板参数的冗余，在某些情况下也可能会导致类型不明确或意外的行为。因此，在实际使用中，还是需要根据具体情况权衡选择是否使用该特性。