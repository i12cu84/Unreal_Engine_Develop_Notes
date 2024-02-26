#include <iostream>
#include <boost/format.hpp>

int main()
{
    int x = 123;
    double y = 4.56;
    std::string z = "hello";

    std::cout << boost::format("x = %1%, y = %2%, z = %3%\n") % x % y % z;

    return 0;
}
