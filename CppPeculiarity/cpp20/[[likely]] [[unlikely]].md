```
#include <iostream>
using namespace std;
int main() {
    int x = 42;
    if ( x > 0)[[likely]] {
        cout << "x is positive" << endl;
    } else [[unlikely]] {
        cout << "x is non-positive" << endl;
    }
}
```
`[[likely]]` 和 `[[unlikely]]` 是 C++20 中的属性关键字，用于给编译器提供分支预测的提示。

这个例子使用了 `[[likely]]` 关键字来提示编译器 `if` 分支中的条件更有可能被满足。如果 `x > 0`，则输出 `"x is positive"`；否则输出 `"x is non-positive"`。