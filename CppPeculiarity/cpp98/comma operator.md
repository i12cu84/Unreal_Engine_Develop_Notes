**逗号运算符重载**：C++98允许重载逗号运算符²。

```cpp
#include <iostream>

class Test {
public:
    Test operator,(const Test& t) {
        std::cout << "Comma operator overloaded!" << std::endl;
        return t;
    }
};

int main() {
    Test t1, t2;
    t1, t2;

    return 0;
}
```