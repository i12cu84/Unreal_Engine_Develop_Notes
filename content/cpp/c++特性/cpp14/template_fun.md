```
#include <iostream>
using namespace std;
template<typename T> auto func(T t) { return t; }
int main() {
    cout << func(4) << endl;
    cout << func(3.4) << endl;
    return 0;
}
```
模板类函数