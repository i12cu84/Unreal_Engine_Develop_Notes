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