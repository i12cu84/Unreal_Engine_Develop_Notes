以下是C++各个版本的标准库特性：

C++98：
引入了以下新的库特性：
RTTI (运行时类型信息)，包括dynamic_cast和typeid
类型转换运算符，如static_cast、dynamic_cast、const_cast和reinterpret_cast
mutable关键字
bool类型
模板实例化
成员模板
export关键字
标准库增加了一些新的内容，包括：本地化支持（locales）、bitset、valarray、auto_ptr、模板化的字符串、I/O流和复数1


C++03：
这是一个主要针对实现者的错误修复版本，以确保更大的一致性和可移植性。这个修订版解决了92个核心语言缺陷报告，125个库缺陷报告，并引入了一个新的语言特性：值初始化2。


C++11：
引入了以下新的库特性：
std::tuple
std::any
std::optional
std::variant
std::string_view
std::invoke
std::apply
std::filesystem
std::byte
并集映射和集合
并行算法
std::sample
std::clamp
std::reduce
前缀求和算法
最大公约数和最小公倍数
std::not_fn
字符串转换为/从数字


C++14：
引入了以下新的库特性：
标准库类型的用户定义字面量
编译时整数序列
std::make_unique


C++17：
引入了以下新的库特性：
概念库
同步缓冲输出流
std::span
比特操作
数学常数
std::is_constant_evaluated
支持数组的std::make_shared
字符串上的开始与结束检查
检查关联容器是否有元素
std::bit_cast


C++20：
引入了以下新的库特性：
概念库
同步缓冲输出流
std::span
比特操作
数学常数
std::is_constant_evaluated
支持数组的std::make_shared
字符串上的开始与结束检查
检查关联容器是否有元素
std::bit_cast


C++23:
标准引入了以下新特性：
模块“std”：这是一个标准库模块，预计将改善编译。
if consteval：这是一个关于即时函数（immediate function）的特性，即consteval函数。
Deducing this（P0847）：这是C++23中最主要的特性之一。msvc在去年3月份就已支持该特性，可以在v19.32之后的版本使用。
std::expected（P0323）：该特性用于解决错误处理的问题，增加了一个新的头文件 <expected>。
Formatted Output（P2093）：该提案就是 std::print()。
import std（P2465）
out_ptr（P1132r8）
auto (x) decay copy（P0849）
简化隐式移动
修复范围for循环中的临时变量
多维和静态运算符[]
Unicode改进
静态constexpr在constexpr函数中