```
#include <iostream>
using namespace std;
constinit int a = 10;
constinit int b = 20;
int main() {
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    return 0;
}
```
在 C++20 中，`constinit` 是一个新的关键字，用于声明具有静态或线程存储期限的变量。
它确保变量具有静态初始化，即零初始化和常量初始化，否则程序将是不合法的。
`constinit` 变量的初始化表达式必须是一个常量表达式，其值可以在编译期计算出。

这个例子定义了两个 `constinit` 变量 `a` 和 `b`，它们都被初始化为常量表达式。
在主函数中，我们打印了这两个变量的值。