#include <boost/signals2/signal.hpp>
#include <iostream>

void slot1() {
    std::cout << "Slot 1 called" << std::endl;
}

void slot2() {
    std::cout << "Slot 2 called" << std::endl;
}

int main() {
    boost::signals2::signal<void()> sig;
    sig.connect(&slot1);
    sig.connect(&slot2);

    std::cout << "Emitting signal..." << std::endl;
    sig();
}
