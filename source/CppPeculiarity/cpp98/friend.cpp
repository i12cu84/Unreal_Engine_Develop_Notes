#include <iostream>
class MyClass {
private:
    int value;
public:
    MyClass(int v) : value(v) {}
    friend void printValue(const MyClass& obj);
};
void printValue(const MyClass& obj) {
    std::cout << "Value: " << obj.value << std::endl;
}
int main() {
    MyClass obj(10);
    printValue(obj); 
    return 0;
}