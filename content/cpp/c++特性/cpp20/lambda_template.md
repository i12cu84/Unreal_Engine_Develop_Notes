```
#include <iostream>
#include <vector>
using namespace std;
template<typename T>
void print_vector(const vector<T>& v) {
    auto lambda = []<typename U>(const U& x) {
        cout << x << " ";
    };
    for (const auto& x : v) {
        lambda(x);
    }
    cout << endl;
}
int main() {
    vector<int> v1{1, 2, 3};
    vector<double> v2{1.1, 2.2, 3.3};
    print_vector(v1);
    print_vector(v2);
}
```
在 C++20 中，Lambda 表达式可以使用模板参数来定义泛型 Lambda。

这个例子定义了一个名为 `print_vector` 的函数模板，它接受一个 `vector` 类型的参数，并使用 Lambda 表达式来打印向量中的元素。
Lambda 表达式使用了模板参数 `U` 来定义泛型 Lambda，然后在循环中使用 Lambda 表达式来打印向量中的元素。
在主函数中，我们创建了两个向量 `v1` 和 `v2`，并分别调用了 `print_vector` 函数来打印它们的元素。