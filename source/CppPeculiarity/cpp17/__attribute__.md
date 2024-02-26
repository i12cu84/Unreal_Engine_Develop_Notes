```
#include <iostream>
// 声明一个函数，在调用时发出警告消息
void myFunction() __attribute__((deprecated));
int main() {
    myFunction(); // 调用已经声明为deprecated的函数
    return 0;
}
// 实现已经声明的函数
void myFunction() {
    std::cout << "This is myFunction." << std::endl;
}
```

1. **告诉编译器不要进行优化（取消优化）**：((optimize("O0")))
   void myFunction() __attribute__((optimize("O0")));
   这告诉编译器不要对 `myFunction` 进行任何优化。
2. **指定函数调用的内联优化级别**：((always_inline))
   int add(int a, int b) __attribute__((always_inline));
   这告诉编译器尽可能地内联 `add` 函数的调用。
3. **标记函数为废弃（deprecated）**：((deprecated))
   void oldFunction() __attribute__((deprecated));
   这会在编译时产生一个警告，表示 `oldFunction` 已被标记为废弃，不推荐使用。
4. **设置函数为纯虚函数**：((pure))
   class MyAbstractClass {
       virtual void myFunction() = 0 __attribute__((pure));
   };
   这将 `myFunction` 标记为纯虚函数，强制派生类提供实现。
5. **强制检查函数的返回值**：((warn_unused_result))
   int getValue() __attribute__((warn_unused_result));
   这告诉编译器检查 `getValue` 函数的返回值是否被使用，并发出警告，如果未使用，则发出警告。
6. **指定函数的可见性**：((visibility("default")))
   void myFunction() __attribute__((visibility("default")));
   这用于设置函数的可见性，例如在动态库中定义的函数，可以设置为 `"default"` 或 `"hidden"`。

这些是一些 `__attribute__` 的示例用法，它们可以用于告诉编译器如何处理特定的函数或变量。请注意，`__attribute__` 是特定于编译器的特性，不同的编译器可能支持不同的属性和选项。因此，在使用时要谨慎考虑可移植性。