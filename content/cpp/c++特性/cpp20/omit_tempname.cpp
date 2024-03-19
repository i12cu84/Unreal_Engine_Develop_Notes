#include <iostream>
#if 1

template<typename T>
struct MyStruct {
    using MyType = typename T::NestedType;
};

struct Example {
    using NestedType = int;
};

int main() {
    MyStruct<Example>::MyType x = 10;
    std::cout << x << std::endl;  // 输出：10
    return 0;
}
#elif 1

template<typename T>
struct MyStruct {
    using MyType = T::NestedType; // 可以省略 typename
};

struct Example {
    using NestedType = int;
};

int main() {
    MyStruct<Example>::MyType x = 10;
    std::cout << x << std::endl;  // 输出：10
    return 0;
}

#endif