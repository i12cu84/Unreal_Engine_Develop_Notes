#include <iostream>
using namespace std;
int main()
{
    int i = 0;
    decltype(i) b = i;
    cout << i << b;
    return 0;
}