#include <boost/rational.hpp>
#include <iostream>

int main() {
    boost::rational<int> r1(1, 2);
    boost::rational<int> r2(3, 4);

    boost::rational<int> result = r1 + r2;

    std::cout << "Result of addition: " << result << std::endl;
}
