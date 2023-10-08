```
#include <iostream>
#include <tuple>
#include <array>
using namespace std;
int main()
{
    std::pair a(1, 2.3f);
    auto [c, d] = a;
    cout << c << endl;
    cout << d << endl;

    std::tuple b(1, 2.2f);
    auto &[e, f] = b;
    e = 2;
    cout << std::get<0>(b) << endl;
    cout << f << endl;

    int array[3]={1,2,3};
    auto [g, h, i] = array;
    cout<<g<<endl;
    cout<<h<<endl;
    cout<<i<<endl;

    struct point{
        int x,y;
    };
    auto [x,y]=point{1,2};
    cout<<x<<endl;
    cout<<y<<endl;

    return 0;
}

```
结构化绑定,可以访问也可以引用改值(对pair,tuple,array和struct都有效)
constexpr auto[x, y] = std::pair(1, 2.3f); // compile error, C++20可以

并且,可以自定义类的结构化绑定
```
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
    /*
        std::tuple_size<Entry> 和 std::tuple_element<N, Entry> 用于告诉编译器自定义类型 Entry 的元组特性：
        std::tuple_size<Entry> 告诉编译器 Entry 类型的元组大小为 2。
        std::tuple_element<0, Entry> 告诉编译器第一个元素的类型是 std::string。
        std::tuple_element<1, Entry> 告诉编译器第二个元素的类型是 int。
        这些特性告诉编译器如何将 Entry 类型的对象视为元组，并且知道每个元素的类型和数量。
    */
}
int main() {
    Entry e;
    auto [name, age] = e;
    cout << name << " " << age << endl; // name 10
    return 0;
}
```