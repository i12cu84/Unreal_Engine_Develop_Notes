#include <iostream>
template<typename T> 
auto funT(T i){return i;}
int main()
{
    std::cout<<funT(1)<<std::endl;
    std::cout<<funT(1.4)<<std::endl;
    std::cout<<funT("123")<<std::endl;
    std::cout<<funT('a')<<std::endl;
    return 0;
}