```
#include <iostream>
int main()
{
    constexpr auto lambda = [](int n)
    { return n * n; };
    // static_assert(lambda(3)!=9,"a");//error
    static_assert(lambda(3) == 9, "a");
}
```
引入了constexpr lambda表达式，可以用于在编译期进行计算。
注意：constexpr函数有如下限制：
函数体不能包含汇编语句、goto语句、label、try块、静态变量、线程局部存储、没有初始化的普通变量，不能动态分配内存，不能有new delete等，不能虚函数。