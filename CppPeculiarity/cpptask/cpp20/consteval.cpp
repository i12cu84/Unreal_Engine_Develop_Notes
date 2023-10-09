#include <iostream>
using namespace std;
consteval int square(int x) {
    return x * x;
}
int main() {
    constexpr int result = square(5);
    cout << "Square of 5 is: " << result << endl;
    return 0;
}