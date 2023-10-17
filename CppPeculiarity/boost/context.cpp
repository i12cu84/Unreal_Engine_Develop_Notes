#include <boost/context/all.hpp>
#include <iostream>

void my_coroutine(boost::context::continuation& c) {
    std::cout << "Coroutine started." << std::endl;
    boost::context::jump_fcontext(c.fcontext, c.fcontext, 0);
    std::cout << "Coroutine resumed." << std::endl;
    boost::context::jump_fcontext(c.fcontext, c.fcontext, 0);
    std::cout << "Coroutine finished." << std::endl;
}

int main() {
    boost::context::stack_allocator alloc;
    boost::context::continuation c1 = boost::context::make_fcontext(alloc.allocate(), 0, my_coroutine);
    boost::context::jump_fcontext(c1.fcontext, c1.fcontext, 0);
}