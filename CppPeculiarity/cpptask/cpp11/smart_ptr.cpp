#include <iostream>
#include <memory>
class MyClass {
public:
    MyClass(int val) : value(val) {
        std::cout << "Constructing MyClass with value " << value << std::endl;
    }
    void Display() {
        std::cout << "MyClass value: " << value << std::endl;
    }
    ~MyClass() {
        std::cout << "Destroying MyClass with value " << value << std::endl;
    }
private:
    int value;
};
int main() {
    // 使用 std::unique_ptr 管理资源（独占所有权）
    std::unique_ptr<MyClass> uniquePtr = std::make_unique<MyClass>(42);
    uniquePtr->Display();
    // 使用 std::shared_ptr 共享资源（共享所有权）
    std::shared_ptr<MyClass> sharedPtr1 = std::make_shared<MyClass>(10);
    std::shared_ptr<MyClass> sharedPtr2 = sharedPtr1; // 共享所有权
    sharedPtr1->Display();
    sharedPtr2->Display();
    // 使用 std::weak_ptr 避免循环引用（不增加引用计数）
    std::shared_ptr<MyClass> sharedPtr3 = std::make_shared<MyClass>(99);
    std::weak_ptr<MyClass> weakPtr = sharedPtr3;    
    // 使用 weak_ptr 锁定 shared_ptr，并检查资源是否存在
    if (auto lockedSharedPtr = weakPtr.lock()) {
        lockedSharedPtr->Display();
    } else {
        std::cout << "Resource is expired." << std::endl;
    }
    // 当 sharedPtr3 超出作用域时，资源被销毁
    return 0;
}
