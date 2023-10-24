```
#include <iostream>
#include <string>
using namespace std;
int main()
{
    // if (init; condition)
    string str = "Hi World";
    if (auto [pos, size] = pair(str.find("Hi"), str.size()); pos != string::npos) {
        std::cout << pos << " Hello, size is " << size;
    }
}
```
if语句初始化扩展, 初始化列表中可以包含多个变量, 每个变量用逗号分隔
另外,std::string::npos 用来表示一个不存在的位置