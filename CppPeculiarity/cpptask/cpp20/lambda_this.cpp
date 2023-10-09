#include <iostream>
using namespace std;
class MyClass {
public:
    void foo() {
        auto lambda = [this] () {
            cout << "The value of m_value is " << m_value << endl;
        };
        lambda();
    }
private:
    int m_value = 42;
};
int main() {
    MyClass instance;
    instance.foo();
    return 0;
}