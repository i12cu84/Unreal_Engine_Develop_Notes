#include <boost/fiber/all.hpp>
#include <iostream>

int main() {
    boost::fibers::fiber fib([]() {
        std::cout << "Fiber started." << std::endl;
    });

    fib.join();
    std::cout << "Fiber finished." << std::endl;
}
