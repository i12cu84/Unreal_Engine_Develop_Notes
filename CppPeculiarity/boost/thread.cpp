
#include <boost/thread.hpp>
#include <iostream>

void worker1() {
    for (int i = 0; i < 5; ++i) {
        std::cout << "Worker 1: " << i << std::endl;
        boost::this_thread::sleep(boost::posix_time::seconds(1));
    }
}

void worker2() {
    for (int i = 0; i < 5; ++i) {
        std::cout << "Worker 2: " << i << std::endl;
        boost::this_thread::sleep(boost::posix_time::seconds(1));
    }
}

int main() {
    boost::thread t1(worker1);
    boost::thread t2(worker2);

    t1.join();
    t2.join();
}