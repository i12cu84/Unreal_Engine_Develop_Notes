#include <boost/safe_numerics/safe_integer.hpp>
#include <iostream>

int main() {
    boost::safe_numerics::safe<int> safe_int1 = 1;
    boost::safe_numerics::safe<int> safe_int2 = 2;

    if (safe_int1 < safe_int2) {
        std::cout << "safe_int1 is less than safe_int2" << std::endl;
    }
}