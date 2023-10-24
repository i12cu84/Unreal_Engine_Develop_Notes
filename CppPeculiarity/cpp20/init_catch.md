C++20以前：
```cpp
auto delay_invoke(F f, Args... args){ 
    return [f, args...] { 
        return std::invoke(f, args...); 
    };
}
```
C++20之后：
```cpp
template<class F, class... Args> 
auto delay_invoke(F f, Args... args){ 
    return [f = std::move(f), ... args = std::move(args)](){ 
        return std::invoke(f, args...); 
    };
}
```

支持初始化捕捉

这两段代码都定义了一个名为delay_invoke的函数模板，该函数接受一个可调用对象f和一些参数args，并返回一个lambda表达式。这个lambda表达式在被调用时会调用f并传入args。

在C++20之前的版本中，lambda表达式通过值捕获f和args。这意味着，当创建lambda表达式时，会对f和每个args进行复制。然后，在lambda表达式中使用这些复制的值。

在C++20及以后的版本中，使用了初始化捕获（也称为广义lambda捕获）。这允许在捕获列表中使用表达式，而不仅仅是变量名。在这个例子中，使用了std::move来移动f和每个args到lambda表达式中。这意味着，当创建lambda表达式时，不再需要复制f和每个args，而是将它们移动到lambda表达式中。这可以提高效率，特别是当f和/或args是大型对象时。
