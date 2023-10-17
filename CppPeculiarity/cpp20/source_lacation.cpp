#include <iostream>
#include <source_location>
void log(const char* message, const std::source_location& location = std::source_location::current()) {
    std::cout << "Info: "
              << location.file_name() << ":"
              << location.line() << " "
              << location.function_name() << " "
              << message << '\n';
}
int main() {
    log("Hello, World!");
    return 0;
}
/*
定义了一个log函数，它接受一个消息和一个std::source_location对象作为参数。
然后，它将消息和源代码位置信息一起输出。使用了std::source_location::current()来获取当前的源代码位置。
在main函数中，调用了log函数并传入了一个消息，但并没有传入std::source_location对象。
因为为location参数提供了默认值，所以当调用log函数时，如果没有提供第二个参数，编译器会自动插入std::source_location::current()
*/