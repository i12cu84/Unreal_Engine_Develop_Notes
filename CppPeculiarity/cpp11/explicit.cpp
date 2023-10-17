#include <iostream>
class MyClass {
public:
    explicit MyClass(int value) : data(value) {
    }
    void printData() {
        std::cout << "Data: " << data << std::endl;
    }
private:
    int data;
};
int main() {
    MyClass obj1(42); // 直接使用 int 构造 MyClass 对象
    obj1.printData();
    // 编译错误：不能进行隐式类型转换
    // MyClass obj2 = 10; 
    return 0;
}
