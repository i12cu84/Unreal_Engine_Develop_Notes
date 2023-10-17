#include <iostream>
#include <vector>
int main()
{
    std::vector<int> vec={0,1,2};
    for(auto iter=vec.begin();iter!=vec.end();++iter)
        std::cout<<*iter<<std::endl;
    for(int i:vec)
        std::cout<<i<<std::endl;
    return 0;
}