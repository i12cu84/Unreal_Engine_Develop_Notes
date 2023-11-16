#include <iostream>
using namespace std;
template<typename T>
T sum(T a)
{
    return a;
}

template<typename T,typename ... arg>
T sum(T a, arg ... args)
{
    return a+sum(args ...);
}

int main()
{
    cout<<sum(1,2,3,4,5)<<endl;
    cout<<sum(1,2,3,4,5,6,7,8,9,10)<<endl;
return 0;
}