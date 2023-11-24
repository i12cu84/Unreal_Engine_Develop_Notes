#include <iostream>
#include <functional>
using namespace std;
#if 0

#elif 1
int main()
{
    int i=333;
    cout<<i<<endl;
}
#elif 1
// fold fun
template <typename... Args>
void print_callback(Args... args)
{
    ((std::cout << args << " "), ...);
    /*
        这里的args是模板参数Args...的简化形式。在折叠表达式中，我们从左到右依次处理每个模板参数。在这个过程中，我们将每个模板参数连接到std::cout，并在它们之间添加一个空格。
        折叠表达式的完整形式如下：
            std::cout << (args1 << " ") << (args2 << " ") << ... << (argsN << " ");
        在这里，args1、args2等表示传入的模板参数。折叠表达式将所有这些参数连接起来，并在它们之间添加空格。最后，我们将连接后的字符串输出到std::cout。
        以示例中的调用print_callback(x, y, str)为例，折叠表达式将执行以下操作：
            std::cout << (x << " ") << (y << " ") << (str << " ");
        这将生成字符串10 3.14 Hello, world!，并将其输出到std::cout。
    */
    std::cout << std::endl;
}
int main()
{
    int x = 10;
    double y = 3.14;
    const char *str = "Hello, world!";
    print_callback(x, y, str);
    return 0;
}



#elif 1
// 这个写法很怪,目前不知道怎么补充

#define VLIB_REGISTER_NODE(x, ...)                              \
    __VA_ARGS__ vlib_node_registration_t x;                     \
    static void __vlib_add_node_registration_##x(void)          \
        __attribute__((__constructor__))                        \
    {                                                           \
        vlib_main_t *vm = vlib_get_main();                      \
        x.next_registration = vm->node_main.node_registrations; \
        vm->node_main.node_registrations = &x;                  \
    }                                                           \
    __VA_ARGS__ vlib_node_registration_t x

#elif 1

typedef void (*CallbackFunc)(int);
void print_callback(int num)
{
    printf("%d\n", num);
}
int main()
{
    int x = 10;
    CallbackFunc callback = print_callback;
    callback(x);
    return 0;
}
#endif