#include <iostream>
using namespace std;
template<class T>
constexpr T pi = T(3.1415926535897932385L);
int main() {
    cout << pi<int> << endl; // 3
    cout << pi<double> << endl; // 3.14159
    return 0;
}