#include <boost/math/constants/constants.hpp>
#include <iostream>

int main() {
    double pi = boost::math::constants::pi<double>();
    std::cout << "Approximate value of pi: " << pi << std::endl;
}