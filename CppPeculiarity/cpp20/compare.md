```
#include <compare>
#include <iostream>
int main()
{
    double foo = 0.0;
    double bar = 1.0;
    if ((foo <=> bar) < 0)
        std::cout << "foo is less than bar";
}
```
"<=>"是一个新的计算符号，逻辑计算符号判断大小，返回正负0三种值