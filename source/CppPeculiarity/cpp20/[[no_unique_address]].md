```
#include <iostream>
using namespace std;
struct Empty {};
struct X {
    int i;
    Empty e;
};
struct Y {
    int i;
    [[no_unique_address]] Empty e;
};
int main() {
    cout << "sizeof(Empty) == " << sizeof(Empty) << endl; // 1
    cout << "sizeof(X) == " << sizeof(X) << endl; // 8
    cout << "sizeof(Y) == " << sizeof(Y) << endl; // 4
}
```
C++20 引入了一个新的属性 `no_unique_address`，它可以用来指示编译器将一个成员子对象与其他非静态数据成员或基类子对象重叠。

这个例子定义了三个结构体：`Empty`、`X` 和 `Y`。
其中，`Empty` 是一个空类，不占用任何空间。`X` 包含一个整型成员 `i` 和一个 `Empty` 类型的成员 `e`，因此它的大小为 8 字节。
而 `Y` 也包含一个整型成员 `i` 和一个 `Empty` 类型的成员 `e`，但是它使用了 `no_unique_address` 属性，因此它的大小为 4 字节。

在这个例子中，我们可以看到使用 `no_unique_address` 属性可以让编译器优化掉空类成员所占用的空间，从而减小结构体的大小。