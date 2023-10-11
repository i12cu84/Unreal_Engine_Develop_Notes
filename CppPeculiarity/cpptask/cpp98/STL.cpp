#include <iostream>
#include <vector>
#include <algorithm>
int main() {
    std::vector<int> v = {3, 1, 4, 1, 5, 9};
    std::sort(v.begin(), v.end());
    for (int i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}