#include <iostream>
class Test {
public:
    Test operator,(const Test& t) {
        std::cout << "Comma operator overloaded!" << std::endl;
        return t;
    }
};
int main() {
    Test t1, t2;
    t1, t2;
    return 0;
}