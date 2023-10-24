```cpp
#include <iostream>
int main()
{
    auto fun=[](auto i){return i;};
    std::cout<<fun(1)<<std::endl;
    std::cout<<fun(1.4)<<std::endl;
    std::cout<<fun("123")<<std::endl;
    std::cout<<fun('a')<<std::endl;
    return 0;
}
```

lambda支持auto类型形参