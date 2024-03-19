```
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
```
修饰的内容不能被忽略，可用于修饰函数，标明返回值一定要被处理，否则编译器会报错