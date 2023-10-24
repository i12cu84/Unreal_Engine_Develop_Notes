#include <iostream>
// 使用 [[nodiscard]] 标记函数的返回值
[[nodiscard]] int divide()
{
    return 1;
}
int main()
{
    int result = divide(); // true
    // divide();  // warning: ignoring return value of 'int divide()', declared with attribute 'nodiscard' [-Wunused-result]
    return 0;
}