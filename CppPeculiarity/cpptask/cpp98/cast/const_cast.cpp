#include <iostream>
using namespace std;
int main()
{
    int a;
    const int &b = a;
    int &c = const_cast<int &>(b);
    cout << a << " " << b << " " << c << endl;
    // 0 0 0
    a = 1;
    cout << a << " " << b << " " << c << endl;
    // 1 1 1
    const_cast<int &>(b) = 2;
    cout << a << " " << b << " " << c << endl;
    // 2 2 2
    c = 3;
    cout << a << " " << b << " " << c << endl;
    // 3 3 3
    return 0;
}
