照例
```
#include <iostream>
union MyUnion
{
    int intValue;
    double doubleValue;
    char charValue;
};
int main()
{
    MyUnion myUnion;
    myUnion.intValue = 42;
    std::cout << "Integer value: " << myUnion.intValue << std::endl;
    myUnion.doubleValue = 3.14;
    std::cout << "Double value: " << myUnion.doubleValue << std::endl;
    myUnion.charValue = 'A';
    std::cout << "Char value: " << myUnion.charValue << std::endl;
    return 0;
}
```
在这个示例中，定义了一个名为 MyUnion 的联合体，其中包含三个成员：intValue（整数）、doubleValue（双精度浮点数）和 charValue（字符）。这些成员共享相同的内存位置，因此在任何时候只能存储其中一个成员的值。
在 main 函数中，创建了一个 MyUnion 类型的变量 myUnion。首先将整数值 42 存储到联合体中，然后将双精度浮点数 3.14 存储到同一联合体中，最后将字符 'A' 存储到联合体中。每次存储都会覆盖前一个值，因为这些值共享相同的内存。
联合体可用于节省内存，但需要小心使用，因为它们没有类型检查，可能导致数据访问错误。它们通常用于特殊情况下，例如在硬件编程或需要特定内存布局的情况下。