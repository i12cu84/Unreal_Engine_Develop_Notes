#include <boost/dispatch/adapted/std/complex.hpp>
#include <boost/dispatch/dispatch.hpp>
#include <iostream>

BOOST_DISPATCH_DEFINE_IF(is_abs_function, boost::dispatch::functor<void(std::complex<double>)>);
BOOST_DISPATCH_DEFINE_IF(is_abs_function, boost::dispatch::functor<void(double)>);

void my_abs(std::complex<double> z) {
    std::cout << "Complex Absolute Value: " << std::abs(z) << std::endl;
}

void my_abs(double x) {
    std::cout << "Absolute Value: " << std::abs(x) << std::endl;
}

int main() {
    std::complex<double> z(3.0, 4.0);
    double x = -5.0;

    my_abs(z);
    my_abs(x);
}
