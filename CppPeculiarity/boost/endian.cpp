#include <boost/endian/conversion.hpp>
#include <iostream>

int main() {
    int nativeValue = 12345;
    int networkValue = boost::endian::native_to_big(nativeValue);

    std::cout << "Native Value: " << nativeValue << std::endl;
    std::cout << "Network Value: " << networkValue << std::endl;
}
