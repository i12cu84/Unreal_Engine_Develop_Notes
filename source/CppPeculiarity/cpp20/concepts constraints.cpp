#include <iostream>
template <typename T>
concept Addable = requires (T a, T b) { a + b; };

template <typename T>
void foo(T a, T b) requires Addable<T> {
std::cout << a + b << std::endl;
}
int main()
{
    return 0;
}