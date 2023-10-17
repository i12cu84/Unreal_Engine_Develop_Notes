#include <boost/phoenix/phoenix.hpp>
#include <iostream>

int main() {
    using namespace boost::phoenix;
    int x = 5;
    int y = 7;

    auto add = arg1 + arg2;
    int result = add(x, y);

    std::cout << "Result of addition: " << result << std::endl;
}
