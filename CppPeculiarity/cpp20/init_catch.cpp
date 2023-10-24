#include <iostream>
#include <functional>
#include <string>
#include <vector>
#if 1
template<class F, class... Args> 
auto delay_invoke(F f, Args... args){ 
    return [f = std::move(f), ... args = std::move(args)](){ 
        return std::invoke(f, args...); 
    };
}
void print_sum(int a, int b) {
    std::cout << (a + b) << std::endl;
}
int main() {
    auto delayed = delay_invoke(print_sum, 3, 4);
    delayed();  // 输出：7
    return 0;
}
#elif 1
template<class F, class... Args> 
auto delay_invoke(F f, Args... args){ 
    return [f, args...] { 
        return std::invoke(f, args...); 
    };
}
void print_sum(int a, int b) {
    std::cout << (a + b) << std::endl;
}
int main() {
    auto delayed = delay_invoke(print_sum, 3, 4);
    delayed();  // 输出：7
    return 0;
}
#elif 1
template<class F, class... Args> 
auto delay_invoke(F f, Args... args){ 
    return [f = std::move(f), ... args = std::move(args)](){ 
        return std::invoke(f, args...); 
    };
}
void Call(int in1,double in2)
{
    std::cout << in1 << " " << in2 << std::endl;
}

int main() {
    delay_invoke(Call, 1, 2.0);
    return 0;
}
#elif 1
auto addInt = [](int fir, int sec)
{ return fir + sec; }; // 只适用于可转换为int的类型    (C++11)
auto addGen = [](auto fir, auto sec)
{ return fir + sec; }; // 任意类型                 (C++14)
auto addDec = [](auto fir, decltype(fir) sec)
{ return fir + sec; }; // 任意但可转换的类型 (C++14)
auto addTem = []<typename T>(T fir, T sec)
{ return fir + sec; }; // 任意但相同的类型   (C++20)

int main()
{
    std::string hello = "Hello ", world = "world";
    std::cout << addInt(2000, 20) << '\t' << addGen(2000, 20) << '\t' << addDec(2000, 20) << '\t' << addTem(2000, 20) << std::endl;
    std::cout << "ERROR" << '\t' << addGen(hello, world) << '\t' << addDec(hello, world) << '\t' << addTem(hello, world) << std::endl;
    std::cout << addInt(true, 2020) << '\t' << addGen(true, 2020) << '\t' << addDec(true, 2020) << '\t' << "ERROR" << std::endl;
}
#endif