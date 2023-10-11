**运算符重载**：C++98允许你重载大多数运算符，这使得你可以定义自己的数据类型，并指定如何对这些类型进行操作¹。

```cpp
#include <iostream>

class Complex {
public:
    Complex(double r, double i) : real(r), imag(i) {}

    Complex operator+(const Complex& c) {
        return Complex(real + c.real, imag + c.imag);
    }

    void print() {
        std::cout << real << " + " << imag << "i" << std::endl;
    }

private:
    double real, imag;
};

int main() {
    Complex c1(1.0, 2.0), c2(2.0, 3.0);
    Complex c3 = c1 + c2;
    c3.print();

    return 0;
}
```