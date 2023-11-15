#include <iostream>
using namespace std;
#define DEF_INT int
typedef int TYP_Int;
int main()
{
    TYP_Int a=1;
    cout << a << endl;
    DEF_INT b=1;
    cout << b << endl;
    return 0;
}
/*
1. **宏定义 (`#define`)**：
    - `#define` 是C/C++中的预处理指令，用于在编译之前对源代码进行处理。
    - 它可以将一个标识符替换为一个固定的值、表达式或运算符。
    - 在你的例子中，`#define DEF_INT int` 将所有出现 `DEF_INT` 的地方都替换为 `int`。
    - 这意味着在编译时，`DEF_INT` 将被替换为 `int`，并且在最终生成的代码中，不再存在 `DEF_INT` 这个标识符。

    优点：
        简单：宏定义是一种简单的文本替换机制。它可以快速地将一个标识符替换为一个值或表达式。
        通用性：宏定义不仅限于类型别名。你可以用它来定义常量、函数、条件编译等。
    缺点：
        缺乏类型安全性：宏定义只是文本替换，不会进行类型检查。如果你不小心在宏定义中使用了错误的表达式，可能会导致难以调试的问题。
        可读性差：宏定义的替换可能会让代码变得难以理解，特别是在复杂的情况下。

2. **`typedef`**：
    - `typedef` 是C/C++中的关键字，用于创建新的类型别名。
    - 它允许你为现有的数据类型定义一个新的名称。
    - 例如，`typedef int MyInt;` 将 `MyInt` 定义为 `int` 的别名。
    - `typedef` 不会进行简单的文本替换，而是真正地声明了一个新的类型。

    优点：
        类型安全：typedef 创建了一个真正的类型别名，具有类型检查。你可以使用它来定义自定义类型，提高代码的可读性和安全性。
        更具表达力：typedef 允许你为不同的数据类型创建更有意义的别名，使代码更易于理解。
    缺点：
        语法稍复杂：相对于宏定义，typedef 的语法稍微复杂一些。
        仅限于类型别名：typedef 只能用于创建类型别名，不能用于其他用途。
*/