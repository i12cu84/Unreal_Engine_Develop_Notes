#include <boost/poly_collection.hpp>
#include <iostream>

class Shape {
public:
    virtual void draw() const = 0;
};

class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a circle" << std::endl;
    }
};

class Square : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a square" << std::endl;
    }
};

int main() {
    boost::poly_collection<Shape> shapes;
    shapes.insert<Circle>();
    shapes.insert<Square>();

    for (const Shape& shape : shapes) {
        shape.draw();
    }
}
