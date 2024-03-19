#include <iostream>
// 定义一个打印日志的宏
#define LOGFUNC(fmt, ...) printf(fmt, ##__VA_ARGS__)
int main() {
    int x = 42;
    double y = 3.14;
    // 使用宏打印日志
    LOGFUNC("x = %d, y = %.2f\n", x, y);
    return 0;
}
/*
当然，让我们来看一个标准示例。假设我们要定义一个宏，用于打印日志信息。我们可以使用 `__VA_ARGS__` 来处理不定数量的参数。以下是一个简单的示例：

在上面的示例中，我们定义了一个名为 `LOGFUNC` 的宏，它接受一个格式化字符串 `fmt` 和可变数量的参数 `...`。在 `main` 函数中，我们使用这个宏来打印变量 `x` 和 `y` 的值。注意，`##__VA_ARGS__` 用于处理可变参数，确保在没有参数时不会产生编译错误。

*/