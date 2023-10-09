#include <iostream>
#include <ranges>
#include <vector>
#include <format>
int main() {
    std::vector vec{1, 12, 32, 54, 10086, -1314};
    auto res = vec | std::views::filter( [] (int n) { return n % 2 == 0; })
                   | std::views::transform( [] (int n) { return n * 2; });
    for (auto v: res) {
        std::cout << v << std::endl;
    }
}
/*
C++20中的ranges库是对算法和迭代器库的扩展和泛化，使它们通过使它们可组合并减少错误而变得更强大。
这个库创建和操作范围视图，这些轻量级对象间接表示可迭代序列（范围）。
以下是ranges库的一些主要特性：
函数组合：ranges库中的算法是惰性的，可以直接在容器上工作，并且可以很容易地组合。
轻量级对象：ranges库创建和操作范围视图，这些轻量级对象间接表示可迭代序列（范围）。
可组合：适配器可以组合成管道，以便在迭代视图时进行它们的操作。

首先创建了一个向量vec。
然后，使用管道符号来组合两个视图：
一个过滤出偶数的视图和一个将每个数字映射到其两倍的视图。
最后，遍历并打印出结果1。
*/