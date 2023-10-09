C++20以前：
auto func = [](auto vec){ 
    // using T = typename decltype(vec)::value_type;
    using T = std::decay_t<decltype(x)>; 
    T copy{x}; 
    T::static_function(); 
    using Iterator = typename T::iterator; 
}

C++20之后：
auto func = []<typename T>(vector<T> vec){ 
    T copy{x}; 
    T::static_function(); 
    using Iterator = typename T::iterator; 
}
简化容器内部类型推断