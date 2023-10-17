#include <iostream>
#include <tuple>
#include <utility>
// 辅助函数：从元组中选择特定索引的元素
template <size_t Index, typename... Ts>
decltype(auto) selectElement(const std::tuple<Ts...>& t) {
    return std::get<Index>(t);
}
// 使用std::integer_sequence来选择元组中的元素
template <typename... Ts, size_t... Is>
auto selectElements(const std::tuple<Ts...>& t, std::index_sequence<Is...>) {
    return std::make_tuple(selectElement<Is>(t)...);
}
// 接受整数序列的主函数
template <typename... Ts, size_t... Indices>
auto selectElementsByIndices(const std::tuple<Ts...>& t, std::index_sequence<Indices...>) {
    return selectElements(t, std::index_sequence<Indices...>());
}
int main() {
    std::tuple<int, double, std::string, char> myTuple(42, 3.14, "Hello", 'A');
    // 选择特定的元素索引（0和2）来创建新的元组
    auto selectedTuple = selectElementsByIndices(myTuple, std::index_sequence<0, 2>());
    // 输出新的元组的元素
    std::cout << std::get<0>(selectedTuple) << std::endl;  // 输出 42
    std::cout << std::get<1>(selectedTuple) << std::endl;  // 输出 "Hello"
    return 0;
}
