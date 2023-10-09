C++20以前：
auto func = [](auto&& ...args) { 
    return foo(std::forward<decltype(args)>(args)...); 
}
C++20之后：
auto func = []<typename …T>(T&& …args){ 
    return foo(std::forward(args)...); 
}

简化完美转发类型推断