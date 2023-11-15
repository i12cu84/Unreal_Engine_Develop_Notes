#include <iostream>  
#include <functional>
using namespace std;
#if 0
class Calculator {  
public:  
    // 绑定回调函数  
    void setOperation(std::function<double(double, double)> operation) {  
        _operation = operation;  
    }
    double calculate(double a, double b) {  
        return _operation(a, b);  
    }
private:  
    std::function<double(double, double)> _operation;  
};
// 回调函数原型声明  
double add(double a, double b){  
    return a + b;  
} 
int main() {  
    Calculator calculator;

    // 设置回调函数  
    calculator.setOperation(add);  
    std::cout << "和：" << calculator.calculate(5, 3) << std::endl;

    return 0;  
}
#elif 1
#include <iostream>

// 原有的 typedef
typedef void (*CallbackFunc)(int);

// 可变参数模板函数
template <typename... Args>
void print_callback(Args... args) {
    // 使用逗号表达式展开参数包
    ((std::cout << args << " "), ...);
    std::cout << std::endl;
}

int main() {
    int x = 10;
    double y = 3.14;
    const char* str = "Hello, world!";

    // 调用可变参数模板函数
    print_callback(x, y, str);

    // 使用原有的 typedef
    CallbackFunc callback = print_callback;
    callback(x);

    return 0;
}
#elif 1
template <typename... Args>
void print_callback(Args... args) {
    ((std::cout << args << " "), ...);
    std::cout << std::endl;
}
int main() {
    int x = 10;
    double y = 3.14;
    const char* str = "Hello, world!";
    print_callback(x, y, str);
    return 0;
}

#elif 1
typedef void (*CallbackFunc)(int);
void print_callback(int num) {  
    printf("%d\n",num);  
}
int main() {  
    int x = 10;
    CallbackFunc callback = print_callback;
    callback(x);
    return 0;  
}
#endif