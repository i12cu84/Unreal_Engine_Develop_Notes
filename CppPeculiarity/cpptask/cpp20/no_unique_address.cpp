#include <iostream>
using namespace std;
struct Empty {};
struct X {
    int i;
    Empty e;
};
struct Y {
    int i;
    [[no_unique_address]] Empty e;
};
int main() {
    cout << "sizeof(Empty) == " << sizeof(Empty) << endl; // 1
    cout << "sizeof(X) == " << sizeof(X) << endl; // 8
    cout << "sizeof(Y) == " << sizeof(Y) << endl; // 4
}