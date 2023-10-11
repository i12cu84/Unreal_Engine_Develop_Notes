#include <iostream>
class MyClass {
public:
    MyClass() : value(0) {}
    void add() const {
        value++;
    }
    void print() const {
        std::cout << "Value: " << value << std::endl;
    }
private:
    mutable int value;
};
int main() {
    MyClass obj;
    obj.add();
    obj.print();
    return 0;
}