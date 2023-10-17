#include <boost/random.hpp>
#include <iostream>

int main() {
    boost::random::mt19937 gen;
    boost::random::uniform_int_distribution<> dist(1, 100);

    for (int i = 0; i < 5; ++i) {
        int random_number = dist(gen);
        std::cout << "Random number: " << random_number << std::endl;
    }
}