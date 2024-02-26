#include <boost/algorithm/string.hpp>
#include <iostream>

int main() {
    std::string input = "Boost String Algorithms";
    boost::to_lower(input);
    std::cout << "Lowercase string: " << input << std::endl;
}
