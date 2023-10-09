目前还没有运行成功
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
C++20引入了协程，它是一种新的并发编程机制，可以帮助开发人员编写更具表现力和可读性的代码。协程可以用于异步编程、生成器、状态机等场景。

下面是一个简单的例子，展示了如何使用协程：

```c++
#include <iostream>
#include <coroutine>

struct generator {
  struct promise_type {
    int current_value;
    auto initial_suspend() { return std::suspend_always{}; }
    auto final_suspend() { return std::suspend_always{}; }
    auto get_return_object() { return generator{this}; }
    auto return_void() {}
    auto yield_value(int value) {
      current_value = value;
      return std::suspend_always{};
    }
  };

  generator(promise_type* p) : p_(p) {}
  ~generator() {}

  void operator++() { p_->current_value++; }
  int operator*() { return p_->current_value; }

  std::coroutine_handle<promise_type> p_;
};

generator counter() {
  co_yield 0;
  co_yield 1;
  co_yield 2;
}

int main() {
  generator g = counter();
  std::cout << *g << std::endl; // prints "0"
  ++g;
  std::cout << *g << std::endl; // prints "1"
  ++g;
  std::cout << *g << std::endl; // prints "2"
}
```

在这个例子中，我们定义了一个名为`counter`的生成器，它可以生成数字0、1和2。在`main`函数中，我们使用了一个名为`g`的生成器对象来遍历这些数字。

如果您想了解更多关于C++20协程的信息，请参阅[官方文档](https://en.cppreference.com/w/cpp/language/coroutines)。