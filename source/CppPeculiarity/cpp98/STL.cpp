#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
int main() {
    std::vector<int> v;
    for (int i = 0; i < 5; i++) 
        v.push_back(i);
#if 1
    for (int i = 0; i < v.size(); i++) 
        std::cout << v[i] << " ";
#elif 1
    std::sort(v.begin(), v.end());
    for (int i : v) 
        std::cout << i << " ";
#elif 1
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) 
        std::cout << *it << " ";
#elif 1
    std::stack<int> s;
    for (int i = 0; i < 5; i++) 
        s.push(i);
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
#elif 1
struct Compare {
    bool operator()(int a, int b) {
        return a < b;
    }
};
    std::sort(v.begin(), v.end(), Compare());
    for (int i : v) {
        std::cout << i << " ";
    }
#endif
    return 0;
}