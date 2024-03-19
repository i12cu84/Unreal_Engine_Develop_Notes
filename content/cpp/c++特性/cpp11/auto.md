```
#include <iostream>
using namespace std;
int main()
{
    int i = 0;
    auto b = i;
    cout << i << b;
    return 0;
}
```

自适应类型,编译时自推导目标变量的类型