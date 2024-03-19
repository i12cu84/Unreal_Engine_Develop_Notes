```cpp
#include <iostream>
using namespace std;
int main()
{
    int i = 0;
    decltype(i) b = i;
    cout << i << b;
    return 0;
}
```

说明符用于获取目标变量的变量类型