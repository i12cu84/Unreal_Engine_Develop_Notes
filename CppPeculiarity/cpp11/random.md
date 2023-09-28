```
#include <time.h>
#include <iostream>
#include <random>
using namespace std;
int main() 
{
    std::default_random_engine random(time(nullptr));
    std::uniform_int_distribution<int> int_dis(0, 100); // 整数均匀分布
    std::uniform_real_distribution<float> real_dis(0.0, 1.0); // 浮点数均匀分布
    for (int i = 0; i < 10; ++i) 
        cout << int_dis(random) << endl;
    for (int i = 0; i < 10; ++i) 
        cout << real_dis(random) << endl;
    return 0;
}
```
随机数功能有所丰富,可以选择概率分布类型