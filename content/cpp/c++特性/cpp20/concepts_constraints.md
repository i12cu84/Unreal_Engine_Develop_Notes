```
template <typename T>
concept Addable = requires (T a, T b) { a + b; };

template <typename T>
void foo(T a, T b) requires Addable<T> {
    std::cout << a + b << std::endl;
}
```
C++20 引入了概念（Concepts）和约束（Constraints）这两个新特性，它们可以用于约束模板类型。概念是指给一组要求（Requirements）所起的名字，是一种具名谓词。每个概念都是谓词，在编译时求值，并在自己被用作约束时成为模板接口的一部分。约束是逻辑操作和操作数的序列，它指定了对模板实参的一些要求。它们可以在 requires 表达式中出现，也可以直接作为概念的主体。有三种类型的约束：合取（conjunction）、析取（disjunction）和不可分割约束（atomic constraint）。对包含遵循以下顺序的操作数的逻辑与表达式进行规范化，确定与一个声明关联的约束：每个声明中受约束的类型模板形参或带占位类型声明的非类型模板形参所引入的约束表达式，按出现顺序；模板形参列表之后的 requires 子句中的约束表达式；简写函数模板声明中每个拥有受约束占位类型的形参所引入的约束表达式；尾部的 requires 子句中的约束表达式。这个顺序决定了在检查是否满足时各个约束时的实例化顺序。受约束的声明只能以相同的语法形式重声明。不要求诊断。

以下是一个使用 C++20 引用约束和概念的例子：
在上面这个例子中，我们定义了一个概念 `Addable`，它要求类型 `T` 支持加法运算符。然后我们定义了一个函数 `foo`，它只接受满足 `Addable` 概念要求的类型作为参数。
这样，我们就可以通过使用概念和约束来限制模板参数，从而提高代码质量和可读性。