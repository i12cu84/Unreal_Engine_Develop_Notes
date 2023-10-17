#include <boost/mixin.hpp>
#include <iostream>

MIXIN_DEFINE(foo);

int main() {
    using namespace mixin;
    object obj;

    add(obj, foo);

    if (has(obj, foo)) {
        std::cout << "Object has foo mixin." << std::endl;
    }
}
