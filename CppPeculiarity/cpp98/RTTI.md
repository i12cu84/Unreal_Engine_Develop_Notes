**RTTI (Run-Time Type Identification)**: 这是一种在运行时确定对象类型的机制。(资源获取即初始化)
例如，`dynamic_cast`和`typeid`就是RTTI的一部分。

```cpp
#include <iostream>
#include <typeinfo>

class Base { virtual void func() {} };
class Derived : public Base {};

int main() {
    Base* base = new Derived;
    if(Derived* derived = dynamic_cast<Derived*>(base)) {
        std::cout << "dynamic_cast successful" << std::endl;
    }
    std::cout << "Type of base: " << typeid(*base).name() << std::endl;
    return 0;
}
```