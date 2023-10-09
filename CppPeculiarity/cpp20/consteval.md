```
#include <iostream>
using namespace std;
consteval int square(int x) {
    return x * x;
}
int main() {
    constexpr int result = square(5);
    cout << "Square of 5 is: " << result << endl;
    return 0;
}
```
在 C++20 中，`consteval` 是一个新的关键字，用于声明只能在编译期间执行的函数。
这使得编译器能够在编译时对 `consteval` 函数进行求值，从而避免了在运行时执行这些函数的开销。
`consteval` 函数被用于要求编译期计算的场景，这些场景对于在运行时计算是不可行的。
`consteval` 函数和普通的 `constexpr` 函数之间的主要区别在于， 
`consteval` 函数必须在编译期执行，并且它们只能在常量表达式上下文中调用。

这个例子定义了一个 `consteval` 函数 `square()`，它在编译期计算了 5 的平方，并将结果存储在 `constexpr` 变量 `result` 中。
输出结果为：

```
Square of 5 is: 25
```
