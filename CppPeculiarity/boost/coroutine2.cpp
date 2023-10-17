#include <boost/coroutine2/all.hpp>
#include <iostream>

void coro(boost::coroutines2::coroutine<int>::pull_type& source) {
    for (int i : source) {
        std::cout << "Received: " << i << std::endl;
    }
}

int main() {
    boost::coroutines2::coroutine<int>::push_type sink(coro);

    sink(1);
    sink(2);
    sink(3);
}
