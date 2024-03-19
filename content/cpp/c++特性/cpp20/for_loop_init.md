```
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v{1, 2, 3};
    for (auto [i, j] = pair{v.begin(), v.end()}; i != j; ++i) {
        cout << *i << " ";
    }
    cout << endl;
}
```
C++20 引入了一种新的 for 循环语法，可以在循环内部初始化变量。

这个例子使用了 C++20 的结构化绑定和 `pair` 类型。
我们可以使用 `pair` 类型来初始化两个变量，然后在 for 循环中使用结构化绑定来将它们分别绑定到迭代器的起始和结束位置。
在循环中，我们可以像往常一样使用 `*i` 来访问当前元素。