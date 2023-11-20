#include <iostream>
using namespace std;
#define HW "Hello World!"
int main()
{
    cout << HW << endl;
#undef HW
    // cout << HW << endl;//error
    return 0;
}