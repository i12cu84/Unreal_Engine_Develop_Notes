#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

int main() {
    using namespace boost::multiprecision;

    cpp_int factorial = 1;
    int n = 100;  // Calculate 100!

    for (int i = 1; i <= n; ++i) {
        factorial *= i;
    }

    std::cout << "100! = " << factorial << std::endl;
}
