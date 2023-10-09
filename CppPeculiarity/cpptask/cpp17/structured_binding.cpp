#include <iostream>
#include <tuple>
#include <array>
using namespace std;
int main()
{
    std::pair a(1, 2.3f);
    auto [c, d] = a;
    cout << c << endl;
    cout << d << endl;

    std::tuple b(1, 2.2f);
    auto &[e, f] = b;
    e = 2;
    cout << std::get<0>(b) << endl;
    cout << f << endl;

    int array[3]={1,2,3};
    auto [g, h, i] = array;
    cout<<g<<endl;
    cout<<h<<endl;
    cout<<i<<endl;

    struct point{
        int x,y;
    };
    auto [x,y]=point{1,2};
    cout<<x<<endl;
    cout<<y<<endl;

    return 0;
}
