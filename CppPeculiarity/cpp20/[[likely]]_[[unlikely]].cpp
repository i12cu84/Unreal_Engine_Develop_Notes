#include <iostream>
using namespace std;
int main() {
    int x = 42;
    if ( x > 0)[[likely]] {
        cout << "x is positive" << endl;
    } else [[unlikely]] {
        cout << "x is non-positive" << endl;
    }
}