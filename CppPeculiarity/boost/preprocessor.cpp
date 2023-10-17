#include <boost/preprocessor.hpp>
#include <iostream>

#define FUNCTION(n, data, elem) \
    int function_##n() { return n; }

BOOST_PP_REPEAT(5, FUNCTION, ~)

int main() {
    std::cout << function_3() << std::endl;
}