```
#include <iostream>
#include <coroutine>
using namespace std;
generator<int> fibonacci(int n) {
    int a = 0, b = 1;
    while (n--) {
        co_yield b;
        auto t = b;
        b += a;
        a = t;
    }
}
int main() {
    for (auto i : fibonacci(10)) {
        cout << i << " ";
    }
    cout << endl;
}
```
C++20 引入了协程，它是一种轻量级的线程，可以在函数内部暂停和恢复执行。

这个例子使用了 `generator` 和 `co_yield` 关键字。`generator` 是 C++20 中的一个新类型，它可以用来定义协程。`co_yield` 关键字可以暂停协程并返回一个值。