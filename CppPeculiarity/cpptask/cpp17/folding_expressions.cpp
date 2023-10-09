#include <iostream>
using namespace std;
template <typename... Ts>
auto sum(Ts... ts)
{
    return (ts + ...);
}
int main()
{
    int a{sum(1, 2, 3, 4, 5)};
    cout << a << endl; // 15
    std::string b{"hello "};
    std::string c{"world"};
    cout << sum(b, c) << endl; // hello world
    return 0;
}