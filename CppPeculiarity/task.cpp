#if 0
#include <iostream>
using namespace std;
int main()
{
    cout<<"task"<<endl;
    return 0;
}
#elif 0
#include <iostream>
#include <functional>

template<typename T>
T adds(T a)
{
    return a;
}

template<typename T,typename ... arg>
T adds(T a,arg... args)
{
    return a+adds(args...);
}

int main()
{
    //使用adds
    // std::cout<<adds(1,2,3,4,5)<<std::endl;
    std::function<int(int, int)> func=adds<int,int>;
    int result1 = func(3, 4);
    std::cout << "Result (using std::bind): " << result1 << std::endl;
    return 0;
}

#elif 1
#include <iostream>
#include <memory>
int main()
{
    int arr[4] = {1, 2, 3, 4};
    int *p1 = std::assume_aligned<16>(arr);
    // 使用p1，而不是arr，以确保从对齐假设中受益。
    // 但是，如果arr没有对齐，无论是否使用p1，程序都具有未定义行为。
    std::cout << *p1 << '\n';
    return 0;
}
#endif