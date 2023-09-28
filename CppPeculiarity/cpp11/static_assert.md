当使用 static_assert 时，可以在编译时检查某些条件是否为真。

下面是一个简单的例子，演示如何使用 static_assert 来检查一个整数是否为正数：
```
#include <iostream>
template <int N>
struct PositiveIntegerCheck {
    static_assert(N > 0, "Input integer must be positive.");
};
int main() {
    constexpr int num = 42;
    PositiveIntegerCheck<num> check_positive; // 此行不会产生编译错误，因为 num 是正数
    // constexpr int negative_num = -5;  // 如果尝试使用负数，将会产生编译错误
    // PositiveIntegerCheck<negative_num> check_negative; // 此行将导致编译错误
    return 0;
}
```
在这个例子中，定义了一个模板结构 PositiveIntegerCheck，它接受一个整数作为模板参数 N。

然后，我们使用 static_assert 来检查 N 是否大于 0。

如果 N 是正数，static_assert 就不会引发错误。

但如果 N 是非正数，编译将失败，并显示指定的错误消息。(把注释的内容去掉就会触发

注意：

1.使用了 constexpr 关键字来声明整数 num，以确保它在编译时已知。这是为了在编译时进行检查。

2.如果取消注释并尝试使用负数，例如 negative_num，则会导致 static_assert 引发错误并停止编译。

3.当编译器检测到 static_assert 条件为假时，它会显示指定的错误消息，并且程序不会继续编译。