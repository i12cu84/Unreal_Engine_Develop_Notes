#include <iostream>
using namespace std;
int main() {
    int x = 42;
    if ( x > 0)[[unlikely]] {
        cout << "x is positive" << endl;
    } else {
        cout << "x is non-positive" << endl;
    }
}
