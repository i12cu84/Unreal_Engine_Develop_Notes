#include <iostream>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at_c.hpp>

int main() {
    boost::fusion::vector<int, std::string, bool> v(10, "Boost", true);
    std::cout << boost::fusion::at_c<0>(v) << std::endl;
    std::cout << boost::fusion::at_c<1>(v) << std::endl;
    std::cout << std::boolalpha << boost::fusion::at_c<2>(v) << std::endl;
    return 0;
}
