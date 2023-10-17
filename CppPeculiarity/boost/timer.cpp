#include <boost/timer/timer.hpp>
#include <iostream>

int main() {
    boost::timer::cpu_timer timer;

    // Perform some time-consuming operation
    for (int i = 0; i < 1000000; ++i) {
        // ...
    }

    timer.stop();
    std::cout << "Elapsed time: " << timer.format() << std::endl;
}
