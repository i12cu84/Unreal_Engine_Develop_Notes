```
#include <iostream>
#include <variant>
int main()
{
    std::variant<int, std::string> myVariant;
    myVariant = 42;
    if (std::holds_alternative<int>(myVariant))
        std::cout << "The variant holds an int: " << std::get<int>(myVariant) << std::endl;
    myVariant = "Hello, Variant!";
    if (std::holds_alternative<std::string>(myVariant))
        std::cout << "The variant holds a string: " << std::get<std::string>(myVariant) << std::endl;
    return 0;
}
```
variant与union比对
    类型安全性：
        std::variant 提供了类型安全性，它在编译时检查类型，确保只能包含其中一个可选类型的值。这意味着你不太可能在运行时遇到类型错误。
        union 不提供类型安全性，你需要自行管理各个成员的类型。这可能导致在访问时出现未定义行为或类型错误。
    内存管理：
        std::variant 自动管理内存，只需要存储当前活跃类型的值，不会浪费额外的内存。
        union 需要为每个可能的类型分配足够的内存，无论是否使用。
    异常安全性：
        std::variant 提供了异常安全性，如果构造或分配值时发生异常，它将确保保持有效状态。
        union 不提供异常安全性，因此需要手动处理异常情况。

所有内置数值类型（如整数、浮点数、字符等）。
用户自定义的结构体和类类型。
指针和智能指针。
函数指针。
STL 容器（如 std::vector、std::string 等）。
其他标准库类型（如 std::tuple、std::optional 等）。
注：它只存储自定义struct或者class时，会显示“无法引用默认构造函数 -- 它是已删除的函数”，可以在前面使用基础类型（例如int），或者使用std::monostate模拟一个空的状态。

struct A {
    A(int i){}  
};
std::variant<A> var;                   //no
std::variant<std::monostate, A> var;   //yes
当然，还有与union的区分比对：
类型安全性：std::variant 提供了类型安全性，它在编译时检查类型，确保只能包含其中一个可选类型的值。这意味着你不太可能在运行时遇到类型错误。union 不提供类型安全性，你需要自行管理各个成员的类型。这可能导致在访问时出现未定义行为或类型错误。
内存管理：std::variant 自动管理内存，只需要存储当前活跃类型的值，不会浪费额外的内存。union 需要为每个可能的类型分配足够的内存，无论是否使用。
异常安全性：std::variant 提供了异常安全性，如果构造或分配值时发生异常，它将确保保持有效状态。union 不提供异常安全性，因此需要手动处理异常情况。
总之,std::variant 的一个重要特性是它能够安全地存储多种不同类型的值，并提供了类型安全的方法来访问这些值。
相比之下，union 在存储非 POD（Plain Old Data）类型时有限制，因为 union 的不同成员共享相同的内存空间，无法保证非 POD 类型的安全存储和访问。而 std::variant 在存储非 POD 类型时能够处理相关的构造和析构，确保类型安全性。
因此，std::variant 提供了比 union 更广泛和类型安全的值存储功能，使其成为处理多种不同类型数据的更好选择。但请注意，std::variant 需要额外的内存来存储类型信息，因此可能会占用更多内存。