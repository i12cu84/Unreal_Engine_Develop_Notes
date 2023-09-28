C++ 标准经历了多个不同的版本和代数，每个版本都引入了新的语言特性和库功能。以下是几个主要的 C++ 标准代数以及它们引入的一些重要内容：

C++98 (第一代)

发布年份：1998 年
重要特性：
类模板和函数模板。
异常处理 (try、catch、throw)。
标准模板库 (STL)，包括容器、迭代器和算法。
auto 关键字用于类型推断。
bool 类型。
const 和 volatile 限定符。
命名空间。

C++11 (第二代)

发布年份：2011 年
重要特性：
自动类型推断 (auto 关键字) 的增强。
Lambda 表达式。
移动语义 (Rvalue 引用和移动构造函数)。
列表初始化 (使用 {} 初始化)。
范围-based for 循环。
nullptr 关键字。
多线程支持 (std::thread、std::mutex 等)。
合并线程 (std::async 和 std::future)。
用户定义字面值。
constexpr 函数。
右值引用 (&&)。
静态断言 (static_assert)。

C++14 (第三代)

发布年份：2014 年
重要特性：
通用的 Lambda 表达式。
二进制字面值 (0b 前缀)。
std::make_unique 函数。
运行期大小数组 (std::dynarray)。
更多的标准库增强。

C++17 (第四代)

发布年份：2017 年
重要特性：
结构化绑定 (structured bindings)。
if 初始化语句。
折叠表达式 (fold expressions)。
嵌套命名空间。
std::optional 类型。
std::variant 类型。
std::filesystem 标准库。
并行算法 (std::parallel 命名空间)。
强化的 constexpr。
其他标准库增强。

C++20 (第五代)

发布年份：2020 年
重要特性：
概念 (Concepts)：用于模板约束的新语言特性。
区间 (Ranges)：包括范围视图、范围适配器等。
协程 (Coroutines)。
三向比较运算符（<=>）。
std::format 函数用于字符串格式化。
std::span 类型，用于表示连续内存区域。
各种标准库增强，如 std::chrono、std::atomic、std::array 等。
这些是 C++ 的几代标准中的一些重要特性。每个新的标准版本都试图引入更多的功能和改进，以提高编程效率、安全性和性能。请注意，C++ 标准正在不断发展，新的标准版本也在不断制定和发布。

C++23 (第六代)

发布年份：2023 年
重要特性：
标准库模块化：C++23将支持使用模块导入标准库，而不是传统的头文件，这将提高编译速度和代码组织方式。标准库模块将使用std作为模块名，例如`import std;`或`import std.io;`。
协程库：C++20引入了无栈协程的语言特性，但没有提供相关的标准库支持。C++23将补充一些协程库，如std::generator、std::task等，让协程更易于使用和开发异步编程。
Executors和Networking：Executors是一种抽象的执行上下文，可以用来控制任务的调度和执行方式。Networking是一个基于Executors的网络编程库，提供了TCP、UDP、DNS等协议的支持。这两个特性都是C++20的候选特性，但因为各种原因被推迟到C++23。
语言小改进：C++23也会对语言本身做一些小改进，如允许在using声明中使用属性、允许在lambda表达式中使用默认模板参数、允许在枚举类中使用运算符重载等。