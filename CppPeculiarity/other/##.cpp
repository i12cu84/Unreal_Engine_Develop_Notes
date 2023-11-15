#include <stdio.h>

// 定义一个打印日志的宏
#define LOGFUNC(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define LOGFUNC2(fmt, ...) printf(fmt, __VA_ARGS__)

int main() {
    int x = 42;
    double y = 3.14;

    // 使用宏打印日志
    LOGFUNC("hello world\n");
    LOGFUNC("x = %d, y = %.2f\n", x, y);

    // LOGFUNC2("hello world\n");//error
    LOGFUNC2("x = %d, y = %.2f\n", x, y);
    return 0;
}

/*
在上面的示例中，我们定义了一个名为 LOGFUNC 的宏，它接受一个格式化字符串 fmt 和可变数量的参数 ...。在 main 函数中，我们使用这个宏来打印变量 x 和 y 的值。注意，##__VA_ARGS__ 用于处理可变参数，确保在没有参数时不会产生编译错误。

## 是一个在宏定义中的特殊符号，用于处理可变数量的参数（variadic arguments）。让我们详细解释一下它的作用：

字符串拼接操作：

在宏定义中，## 用于将多个标识符（identifier）或字符串常量拼接成一个更大的标识符或字符串常量。
通常用于构建复杂的宏名称或字符串。
例如，假设我们要定义一个宏，用于生成函数的名称。我们可以这样做：
#define DECLARE_FUNCTION(name) void func_##name() { 函数实现 }

在这里，## 将 func_ 和 name 拼接在一起，生成了一个新的函数名。
处理可变参数：

在宏定义中，## 用于处理可变数量的参数。
当宏的参数列表为空时，## 可以防止在宏展开时产生多余的逗号。
例如，考虑以下宏定义：
#define LOGFUNC(fmt, ...) printf(fmt, ##__VA_ARGS__)

这里的 ##__VA_ARGS__ 用于处理可变参数，确保在没有参数时不会产生编译错误。
总之，## 是一个强大的宏操作符，使得宏定义可以更灵活地处理不定数量的参数和字符串拼接。
*/