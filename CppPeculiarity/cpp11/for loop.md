```
#include <iostream>
#include <vector>
int main()
{
    std::vector<int> vec={0,1,2};
    for(auto iter=vec.begin();iter!=vec.end();++iter)//根据指针遍历
        std::cout<<*iter<<std::endl;
    for(int i:vec)//直接遍历
        std::cout<<i<<std::endl;
    return 0;
}
```
基于范围的for循环