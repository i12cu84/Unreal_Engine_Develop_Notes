#include <vector>
using namespace std;
int main()
{
    int x;
    auto func = [&x]
    <typename T>
    (vector<T> vec){ 
        T copy{x}; 
        T::static_function(); 
        using Iterator = typename T::iterator; 
    };

}
