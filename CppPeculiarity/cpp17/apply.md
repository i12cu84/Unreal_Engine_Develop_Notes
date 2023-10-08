```
#include <iostream>
#include <tuple>
#include <utility>
int add(int a, int b) {
    return a + b;
}
int main() {
    std::tuple<int, int> myTuple(3, 4);
    int result = std::apply(add, myTuple);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
```

```
#include <iostream>
#include <tuple>
#include <utility>
int sum()
{
    return 0;
}
template <typename... Args>
int sum(Args... args)
{
    std::tuple<Args...> argTuple(args...);
    return std::apply([](auto... values)
                      { return (values + ...); },
                      argTuple);
}
int main()
{
    int result = sum(1, 2, 3);
    std::cout << "Sum: " << result << std::endl;
    int result2 = sum(3, 4, 5, 6);
    std::cout << "Sum: " << result2 << std::endl;
    return 0;
}

```
std::apply 是 C++17 中引入的函数，用于将参数包（parameter pack）中的参数传递给一个函数，它可以帮助在运行时动态地调用函数，而不需要提前知道参数的数量。
std::apply 允许我们在运行时将参数包的内容传递给一个函数，这对于需要动态处理不同数量的参数的情况非常有用。