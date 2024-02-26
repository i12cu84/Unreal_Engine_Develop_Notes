#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
int main() {
    boost::multiprecision::cpp_int big_number = 1234567890123456789012345678901234567890;
    std::cout << "Big number squared: " << big_number * big_number << std::endl;
}