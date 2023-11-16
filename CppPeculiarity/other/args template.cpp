#include <iostream>
#include <string>
#include <functional>
using namespace std;

template <typename... Args>
void print_callback(Args... args) {
    ((std::cout << args << endl), ...);
    std::cout << std::endl;
}
int main() {
    int x = 10;
    double y = 3.14;
    const char* str = "Hello, world!";
    string st="sp";

    print_callback(x, y, str,st);
    return 0;
}