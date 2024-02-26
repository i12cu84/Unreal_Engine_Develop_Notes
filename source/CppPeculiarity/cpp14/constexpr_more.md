```cpp
/*
constexpr int factorial(int n) { // C++14 和 C++11均可
    return n <= 1 ? 1 : (n * factorial(n - 1));
}
*/
constexpr int factorial(int n) { // C++11中不可，C++14中可以
    int ret = 0;
    for (int i = 0; i < n; ++i) {
        ret += i;
    }
    return ret;
}
/*
constexpr int func(bool flag) { // C++14 和 C++11均可
    return 0;
}
*/
constexpr int func(bool flag) { // C++11中不可，C++14中可以
    if (flag) return 1;
    else return 0;
}  
int main()
{
    return 0;
} 
```

constexpr 关键字是 C++11 引入的，用于在编译时进行计算，而不是在运行时。
而 C++14 引入了更多返回值