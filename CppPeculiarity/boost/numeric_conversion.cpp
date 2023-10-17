#include <boost/numeric/conversion/cast.hpp>
#include <iostream>

int main() {
    try {
        double value = 42.5;
        int result = boost::numeric_cast<int>(value);
        std::cout << "Converted value: " << result << std::endl;
    } catch (const boost::numeric::bad_numeric_cast& ex) {
        std::cerr << "Conversion error: " << ex.what() << std::endl;
    }
}
