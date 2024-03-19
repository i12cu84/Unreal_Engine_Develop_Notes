#include <boost/lexical_cast.hpp>
#include <iostream>

int main() {
    try {
        std::string str_value = "42";
        int int_value = boost::lexical_cast<int>(str_value);
        std::cout << "Converted int value: " << int_value << std::endl;
    } catch (const boost::bad_lexical_cast& e) {
        std::cerr << "Conversion error: " << e.what() << std::endl;
    }
}