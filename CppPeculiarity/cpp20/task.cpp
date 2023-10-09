#include <iostream>
#include <span>

void printNumbers (std::span<int> numbers) {
    for (int number : numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;
}

int main () {
    int arr [] = {1, 2, 3, 4, 5};
    std::span<int> numbers (arr, 3); // 使用数组arr的前3个元素创建span
    printNumbers (numbers);
    return 0;
}