#include <boost/stacktrace.hpp>
#include <iostream>

void printStackTrace() {
    boost::stacktrace::stacktrace st;
    std::cout << st << std::endl;
}

int main() {
    printStackTrace();
}