#include <boost/contract/core/virtual.hpp>
#include <iostream>

struct MyInterface {
    virtual void foo() = 0;
};

struct MyImplementation : MyInterface {
    BOOST_CONTRACT_OVERRIDE(void foo()) {
        BOOST_CONTRACT_PRECONDITION([] { /* Precondition check */ });
        BOOST_CONTRACT_OLD([] { /* Old state check */ });

        foo_impl();

        BOOST_CONTRACT_POSTCONDITION([] { /* Postcondition check */ });
        BOOST_CONTRACT_OLD([] { /* Old state check */ });
    }
private:
    void foo_impl() {
        // Actual implementation
        std::cout << "foo() called" << std::endl;
    }
};

int main() {
    MyImplementation obj;
    obj.foo();
}
