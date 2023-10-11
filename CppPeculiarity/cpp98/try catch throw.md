**异常处理**：C++98引入了异常处理机制，包括`try`、`catch`和`throw`关键字¹。

```cpp
#include <iostream>

void mightGoWrong() {
    bool error = true;

    if (error) {
        throw "Something went wrong!";
    }
}

int main() {
    try {
        mightGoWrong();
    }
    catch (const char* e) {
        std::cout << "Caught an exception: " << e << std::endl;
    }

    return 0;
}
```