```
#include <iostream>
#include <iomanip>
using namespace std;
int main() {
    string str = "hello world";
    cout << str << endl;
    cout << std::quoted(str) << endl;
    return 0;
}
```
输出带双引号