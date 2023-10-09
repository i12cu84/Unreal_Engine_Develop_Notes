```
#include <atomic>
#include <iostream>

int main() {
  std::atomic<int> counter{0};
  auto increment = [&counter]() { ++counter; };

  std::thread t1(increment);
  std::thread t2(increment);

  t1.join();
  t2.join();

  std::cout << "Counter value: " << counter << std::endl;
}
```
同步库
C++20引入了一些新的同步原语，例如`std::atomic_ref`、`std::atomic_flag_test_and_set`和`std::atomic_flag_clear`等。这些原语可以用于多线程编程，以确保线程安全。例如，您可以使用`std::atomic_ref`来实现一个线程安全的计数器：

在这个例子中，我们使用了一个原子计数器来确保两个线程不会同时访问和修改计数器的值。这样可以避免竞态条件和数据竞争。

如果您想了解更多关于C++20同步原语的信息，请参阅[官方文档](https://en.cppreference.com/w/cpp/atomic)。