#include <iostream>
namespace my_namespace {
    int var = 10;
}
int main() {
    std::cout << my_namespace::var << std::endl;
    return 0;
}