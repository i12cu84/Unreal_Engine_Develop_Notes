#include <iostream>
#include <functional>
using namespace std;
#if 0

#elif 1
}

#elif 1

// This pair of macros is used to help implement GENERATED_BODY() and GENERATED_USTRUCT_BODY()
#define BODY_MACRO_COMBINE_INNER(A,B,C,D) A##B##C##D
#define BODY_MACRO_COMBINE(A,B,C,D) BODY_MACRO_COMBINE_INNER(A,B,C,D)

// Include a redundant semicolon at the end of the generated code block, so that intellisense parsers can start parsing
// a new declaration if the line number/generated code is out of date.

/*
#define GENERATED_BODY_LEGACY(...) BODY_MACRO_COMBINE(CURRENT_FILE_ID,_,__LINE__,_GENERATED_BODY_LEGACY);
#define GENERATED_BODY(...) BODY_MACRO_COMBINE(CURRENT_FILE_ID,_,__LINE__,_GENERATED_BODY);
*/

#include <iostream>
#include <string>

// 定义一个示例字符串
const std::string str1 = "Hello";
const std::string str2 = "World";

// 使用 BODY_MACRO_COMBINE_INNER 宏将两个字符串连接在一起
std::string combined_string = BODY_MACRO_COMBINE_INNER(str1, " ", str2);

// 输出组合后的字符串
std::cout << combined_string << std::endl;

// 输出结果：Hello World

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