```cpp
#include <iostream>
#include <string_view>
int main() {
    std::string myString = "Hello, World!";// 创建一个字符串
    std::string_view myStringView(myString);// 创建一个string_view，指向myString的数据
    std::cout << "String View: " << myStringView << std::endl;// 输出字符串视图的内容
    std::cout << "Length: " << myStringView.length() << std::endl;// 访问字符串视图的长度
    std::string_view subStringView = myStringView.substr(0, 5);// 使用字符串视图的substr方法创建一个子视图
    std::cout << "Sub String View: " << subStringView << std::endl;// 输出子视图的内容
    return 0;
}
```
std::string_view 是C++17引入的一种字符串视图，它允许你轻松地处理字符串数据，而不需要复制它们。

---------------------------------------------------------------------------------------------------------------------------

使用std::string_view与将字符串复制到std::string之间的主要区别在于内存管理和性能:

内存管理：使用std::string_view时，它只是一个轻量级的“视图”，它不拥有实际的字符串数据，而是指向现有字符串的内存区域。这意味着它不会为字符串数据分配额外的内存，也不会复制字符串。使用std::string时，它会为字符串分配内存并进行复制，因此会有两份内存：原始字符串和std::string中的复制。

性能：使用std::string_view通常比将字符串复制到std::string更高效，因为它避免了额外的内存分配和复制操作。

生命周期管理：使用std::string_view时，你需要确保原始字符串在std::string_view仍然在使用时保持有效。如果原始字符串的生命周期比std::string_view更短，你可能会遇到悬垂指针的问题。使用std::string时，它会拥有自己的内存副本，因此不需要担心原始字符串何时会被释放。

因此，当你只需要读取字符串数据而不需要修改它时，std::string_view提供了一种高效的方式来处理字符串。但是请注意，如果你需要对字符串进行修改或者需要确保字符串的生命周期，那么你可能需要使用std::string来拥有自己的内存副本。

---------------------------------------------------------------------------------------------------------------------------

另外,其与别名(Alias)的区别:

内存管理：别名本质上是一个名称别称，不会改变内存管理方式。如果你使用别名来引用字符串，仍然需要考虑原始字符串的生命周期和内存管理。std::string_view是一个包含有关字符串的元信息（指针和长度）的轻量级对象，不拥有内存，因此可以更安全地引用现有字符串。

字符串拷贝：使用别名不会阻止你在需要时拷贝字符串数据。如果你通过别名引用字符串，并在需要时对其进行拷贝，那么内存复制仍然会发生。std::string_view不允许直接拷贝字符串数据，它只提供了对原始数据的引用，因此可以避免不必要的复制。

性能：std::string_view通常比使用别名更高效，因为它不需要额外的内存分配和拷贝操作。

可移植性：std::string_view是C++标准库的一部分，因此具有跨不同编译器和平台的良好可移植性。别名可能会受限于特定编译器或编译选项。

总的来说，std::string_view提供了更安全、更高效、更可移植的方式来处理字符串，特别是当你需要读取字符串而不需要修改它时。使用别名可能会更灵活，但需要更多的注意力来管理内存和复制操作。因此，根据具体的需求和性能要求，你可以选择使用适当的工具。

---------------------------------------------------------------------------------------------------------------------------
```cpp
#include <iostream>
#include <string_view>
int main() {
    std::string originalString = "Hello, World!";
    std::string_view stringView(originalString);
    std::cout << "Original View: " << originalString << std::endl;
    std::cout << "String View: " << stringView << std::endl;

    originalString += " This is a new part.";
    std::cout << "Original View: " << originalString << std::endl;
    std::cout << "String View: " << stringView << std::endl;
    return 0;
}
```
```
Original View: Hello, World!
String View: Hello, World!
Original View: Hello, World! This is a new part.
String View: !//你看这里出了问题呢,看看 ↓ 的注意
```
特别注意:修改std::string可能会导致动态内存重新分配和复制，这样原始字符串的内存地址可能会发生变化，但std::string_view仍然会引用先前的内存位置，因此在修改std::string后，要小心确保std::string_view的引用不会导致未定义的行为。如果你使得std::string的内存重新分配和复制，与之前相关的std::string_view会变得无效（悬挂指针）。这是因为std::string_view仅仅是一个对std::string内存的视图，它不会跟踪std::string内部的内存管理或复制操作。


---------------------------------------------------------------------------------------------------------------------------

 一、核心特点

非拥有内存（只读视图）

仅存储指向原始字符串的指针和长度，不管理内存生命周期，不分配或释放内存。

只读操作：无法通过 string_view 修改底层字符串数据。

轻量高效

构造、复制开销极小（仅复制指针和长度），适合高频调用场景。

避免临时 std::string 的构造，尤其处理字面量或大字符串时性能显著提升。

兼容多种字符串类型

可接受 std::string、C 风格字符串（const char*）、字符数组及字面量作为数据源。

操作与 std::string 类似

支持 size()、substr()、find()、compare() 等常见操作，但 substr() 复杂度为 O(1)（仅调整指针和长度，无拷贝）。

无空终止符保证

不以 \0 结尾，需通过 size() 确定边界，直接使用 data() 可能越界。

🛠 二、基本用法

1. 构造与初始化
   
```cpp
#include <string_view>
#include <string>

std::string str = "Hello, C++17";
const char* cstr = "C-style string";

// 从 std::string 构造
std::string_view sv1(str); 

// 从 C 字符串构造
std::string_view sv2(cstr); 

// 从字面量直接构造
std::string_view sv3("Literal"); 

// 指定指针和长度
char arr[] = {'A', 'B', 'C'};
std::string_view sv4(arr, 3); 
```

2. 常用操作
```cpp
std::string_view sv = "Hello, World";

// 获取长度
size_t len = sv.size(); // 12

// 获取子串（O(1) 操作）
std::string_view sub = sv.substr(0, 5); // "Hello"

// 查找字符
size_t pos = sv.find('W'); // 7

// 移除前缀/后缀
sv.remove_prefix(7);    // "World"
sv.remove_suffix(1);    // "Worl"

// 遍历字符
for (char c : sv) { /* ... */ }
```
3. 作为函数参数（高效传递）
```cpp
// 推荐：避免拷贝，兼容多种字符串类型
void process_text(std::string_view text) {
    if (text.empty()) return;
    auto substr = text.substr(0, 10); // 无拷贝操作
}

// 调用示例
process_text("Literal");       // 字面量
process_text(std::string("...")); // std::string
process_text(cstr);            // C 字符串
```
⚡ 三、性能优势场景
避免临时字符串拷贝

传递字面量时，const std::string& 会触发临时 std::string 构造（可能堆分配），而 string_view 无此开销68。

高效子串操作

sv.substr() 仅返回新视图，而 str.substr() 需复制数据8。

```cpp
// 对比性能（10万次调用）
std::string s = "long_string......";
// string::substr：耗时 17ms (涉及拷贝)
// string_view::substr：耗时 1.6ms (仅指针操作):cite[8]
```
解析大文本/日志

处理内存映射文件或网络数据时，无需复制原始数据46。

⚠️ 四、注意事项
生命周期管理（关键！）

原始字符串必须比 string_view 存活更久，否则导致悬垂指针：

```cpp
std::string_view sv;
{
    std::string temp = "temporary";
    sv = temp;      // sv 指向 temp 的内存
} // temp 析构，sv 失效！
std::cout << sv;    // 未定义行为！:cite[5]:cite[6]
```
不支持修改底层数据

若需修改字符串，需转为 std::string：

```cpp
std::string str2 = std::string(sv); // 复制数据
str2[0] = 'X'; // 允许修改
```
不保证空终止符

需用 size() 控制边界，避免直接传递 data() 给 C 函数69。
