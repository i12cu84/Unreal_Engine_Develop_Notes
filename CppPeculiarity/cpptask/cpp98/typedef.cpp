#include <iostream>
#include <vector>
typedef std::vector<int> IntVector;
int main() {
    IntVector v = {1, 2, 3, 4, 5};
    for (int i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}