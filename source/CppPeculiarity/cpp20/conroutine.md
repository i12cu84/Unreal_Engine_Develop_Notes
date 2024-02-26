```
#if 1
#include <coroutine>
#include <iostream>
#include <stdexcept>
#include <thread>
 
auto switch_to_new_thread(std::jthread& out)
{
    struct awaitable
    {
        std::jthread* p_out;
        bool await_ready() { return false; }
        void await_suspend(std::coroutine_handle<> h)
        {
            std::jthread& out = *p_out;
            if (out.joinable())
                throw std::runtime_error("Output jthread parameter not empty");
            out = std::jthread([h] { h.resume(); });
            // Potential undefined behavior: accessing potentially destroyed *this
            // std::cout << "New thread ID: " << p_out->get_id() << '\n';
            std::cout << "New thread ID: " << out.get_id() << '\n'; // this is OK
        }
        void await_resume() {}
    };
    return awaitable{&out};
}
 
struct task
{
    struct promise_type
    {
        task get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
};
 
task resuming_on_new_thread(std::jthread& out)
{
    std::cout << "Coroutine started on thread: " << std::this_thread::get_id() << '\n';
    co_await switch_to_new_thread(out);
    // awaiter destroyed here
    std::cout << "Coroutine resumed on thread: " << std::this_thread::get_id() << '\n';
}
 
int main()
{
    std::jthread out;
    resuming_on_new_thread(out);
}
#else
#include <coroutine>
#include <cstdint>
#include <exception>
#include <iostream>
 
template<typename T>
struct Generator
{
    // The class name 'Generator' is our choice and it is not required for coroutine
    // magic. Compiler recognizes coroutine by the presence of 'co_yield' keyword.
    // You can use name 'MyGenerator' (or any other name) instead as long as you include
    // nested struct promise_type with 'MyGenerator get_return_object()' method.
 
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;
 
    struct promise_type // required
    {
        T value_;
        std::exception_ptr exception_;
 
        Generator get_return_object()
        {
            return Generator(handle_type::from_promise(*this));
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() { exception_ = std::current_exception(); } // saving
                                                                              // exception
 
        template<std::convertible_to<T> From> // C++20 concept
        std::suspend_always yield_value(From&& from)
        {
            value_ = std::forward<From>(from); // caching the result in promise
            return {};
        }
        void return_void() {}
    };
 
    handle_type h_;
 
    Generator(handle_type h) : h_(h) {}
    ~Generator() { h_.destroy(); }
    explicit operator bool()
    {
        fill(); // The only way to reliably find out whether or not we finished coroutine,
                // whether or not there is going to be a next value generated (co_yield)
                // in coroutine via C++ getter (operator () below) is to execute/resume
                // coroutine until the next co_yield point (or let it fall off end).
                // Then we store/cache result in promise to allow getter (operator() below
                // to grab it without executing coroutine).
        return !h_.done();
    }
    T operator()()
    {
        fill();
        full_ = false; // we are going to move out previously cached
                       // result to make promise empty again
        return std::move(h_.promise().value_);
    }
 
private:
    bool full_ = false;
 
    void fill()
    {
        if (!full_)
        {
            h_();
            if (h_.promise().exception_)
                std::rethrow_exception(h_.promise().exception_);
            // propagate coroutine exception in called context
 
            full_ = true;
        }
    }
};
 
Generator<std::uint64_t>
fibonacci_sequence(unsigned n)
{
    if (n == 0)
        co_return;
 
    if (n > 94)
        throw std::runtime_error("Too big Fibonacci sequence. Elements would overflow.");
 
    co_yield 0;
 
    if (n == 1)
        co_return;
 
    co_yield 1;
 
    if (n == 2)
        co_return;
 
    std::uint64_t a = 0;
    std::uint64_t b = 1;
 
    for (unsigned i = 2; i < n; ++i)
    {
        std::uint64_t s = a + b;
        co_yield s;
        a = b;
        b = s;
    }
}
 
int main()
{
    try
    {
        auto gen = fibonacci_sequence(10); // max 94 before uint64_t overflows
 
        for (int j = 0; gen; ++j)
            std::cout << "fib(" << j << ")=" << gen() << '\n';
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Exception: " << ex.what() << '\n';
    }
    catch (...)
    {
        std::cerr << "Unknown exception.\n";
    }
}
#endif
```
背景

C++ 20 内引入了 co_yield, co_await, co_return 三个关键字。任何函数在使用了这三个关键字中的任何一个后，都会被编译器视作协程函数，进行一些特殊编译处理。

协程介绍

协程其实就是用户态的线程（粗略的定义），协程的切换完全是在用户态进行，不需要陷入到内核态，因此切换的开销远小于线程。

协程分为有栈协程和无栈协程。

有栈协程顾名思义，每个协程都会分配栈，这会对协程的并发数量造成限制。例如Golang中每个协程默认栈大小为2KB（可能会发生扩栈）。好处是有栈协程就类似于普通的函数调用，且代码没有侵入性，可以轻松兼容现有的代码（因为有独立的栈）

无栈协程高度依赖于编译器的处理，不需要单独的为每个协程保存栈，且切换成本更低。（因为不用切换栈）

C++ 20 Coroutine

对于C++20, 语言只提供了最基础的语法支持，更多协程的标准库支持需要到C++23才能就绪。

对于协程来说，有两个概念，即挂起与恢复。

挂起：一个协程挂起后，将保存现场，暂停当前的执行。

恢复：一个协程在挂起后，可以被恢复执行。

每个协程，拥有以下几个对象：

Promise 对象 在堆上储存。
Coroutine Handle 协程句柄，借此对协程进行操作。
Coroutine State 协程的状态，包括协程启动时提供的参数（按值复制），该状态为动态分配，编译器生成的代码会对其进行管理。
调用过程

我们先对该协程函数进行粗糙的定义：
Coroutine F (t1 a1, t2 a2);
 
class Coroutine {
    public :
　　   struct promise_type {
                Coroutine get_return_object();
            };
}
int main() {
    auto ret = coawait F(1, 2);
} 

下面我们将介绍该协程函数的启动过程。（讨论的是编译器生成的代码）

当一个协程函数被调用后，首先会使用 operator Promise::new 构造coroutine state。（若不存在，则使用new）

在此之后，将会拷贝参数(a1, a2)到 Coroutine State 中进行保存。

其次，会调用Promise的构造函数，对其进行构造。(Promise的位置由编译器决定，具体的细节我没有找到资料，不过猜测是控制在了coroutine handler的一个固定的相对位置上）

然后会调用 promise.get_return_object() 获取返回的Coroutine对象。（该对象会作为函数的返回值

在此之后，会调用 coawait promise.initial_suspend() (coawait后面介绍）
 
 
这是一个粗略的启动过程。下面将介绍coawait
 
co_await
该关键字作用于一个Awaitable对象上。在上面的例子里，作用在了F的返回值上，也就是类型Coroutine上。
co_await 用于将函数的执行权交给一个协程，并在该协程挂起后，恢复执行co_await下面的代码。
Awaitable
作为co_await作用的对象，一个awaitable对象需要实现以下几个函数：
await_ready await
await_suspend(coroutine_handle<>)
await_resume
在我们调用 co_await <expr>时，实质上等价于编译器执行以下过程：

当通过<expr>拿到awaitable对象后（详细参考cppreference），首先会调用awaitable::await_ready()，如果返回的是true,那就直接跳过以下的所有流程，不需要挂起（可以避免性能开销，例如结果已经知道了，或者可以同步计算时）

如果返回的是false, 那么就需要进入挂起的流程。此时，当前协程的变量状态、暂停点等信息将会保存到coroutine state中。然后，awaiter::await_suspend(handle)将会被调用（这里的handle代表着当前协程的handle）。

若await_suspend返回的是void，那么控制权将立即返回给调用方。

若返回的是bool,当返回为true时，同上。返回为false时，将恢复当前协程。

最终awaiter::await_resume()将被调用。其返回值将作为整个co_await <expr>的返回值。

关键词	功能
co_await	挂起当前协程，并等待另一个操作完成
co_yield	将一个值返回给协程的调用者，并挂起当前协程
co_return	从协程中返回值，表示协程的结束

参考文献
https://www.cnblogs.com/dorbmon/p/17321964.html
https://blog.csdn.net/forcj/article/details/113768036
https://en.cppreference.com/w/cpp/language/coroutines
https://blog.csdn.net/qq_21438461/article/details/131230589