#include<iostream>
using namespace std;
// 需要实现相关的tuple_size和tuple_element和get<N>方法。
class Entry {
public:
    Entry():name_("name") ,age_(10){ }
    std::string name_;
    int age_;
};
template <size_t I>
auto get(const Entry& e) {
    if constexpr (I == 0) return e.name_;
    else if constexpr (I == 1) return e.age_;
}
namespace std {
    template<> struct tuple_size<Entry> : integral_constant<size_t, 2> {};
    template<> struct tuple_element<0, Entry> { using type = std::string; };
    template<> struct tuple_element<1, Entry> { using type = int; };
}
int main() {
    Entry e;
    auto [name, age] = e;
    cout << name << " " << age << endl; // name 10
    return 0;
}