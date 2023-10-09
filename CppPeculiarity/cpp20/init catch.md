C++20以前：
template<class F, class... Args> 
auto delay_invoke(F f, Args... args){ 
    return [f, args...]{ 
        return std::invoke(f, args...); 
    } 
}
C++20之后：
template<class F, class... Args> 
auto delay_invoke(F f, Args... args){ 
    return [f = std::move(f), args = std::move(args)...](){ 
        return std::invoke(f, args...); 
    } 
}

支持初始化捕捉