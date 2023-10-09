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