```
#include <iostream>  
using namespace std;

int main()
{
    int a=1;
    int&b =a;
    remove_reference<decltype(b)>::type c = a;
    printf("a%d b%d c%d \n",a,b,c);

    a=2;
    printf("a%d b%d c%d \n",a,b,c);

    b=3;
    printf("a%d b%d c%d \n",a,b,c);

    c=4;
    printf("a%d b%d c%d \n",a,b,c);
    return 0;
}
```

C++的remove_reference是一个编译时的函数模板，用于移除传入类型的引用。
这个模板函数是由<utility>库提供的，主要用于减少代码的复杂性，使代码更加简洁。
remove_reference适用于移除类型层次结构中的引用，例如从函数参数中移除引用，以便在函数内部处理原始类型。

简单说就是引用移除