#include <iostream>
#include <string>
using namespace std;

typedef void (*CallbackFunc)(int,double);

template <typename... Args>
void print_callback(Args... args) {
    ((std::cout << args << endl), ...);
    std::cout << std::endl;
}

int main() {
    int x = 10;

    CallbackFunc callback = print_callback;
    callback(x,x);

    return 0;
}