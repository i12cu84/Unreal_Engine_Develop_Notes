#include <iostream>
#include <string>
#include <functional>
using namespace std;

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