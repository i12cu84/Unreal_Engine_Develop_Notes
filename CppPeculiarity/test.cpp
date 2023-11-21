#include <iostream>  
#include <functional>
using namespace std;
#if 0

#elif 1


#elif 1
//这个写法很怪,目前不知道怎么补充

#define VLIB_REGISTER_NODE(x,...)                                       \
    __VA_ARGS__ vlib_node_registration_t x;                             \
static void __vlib_add_node_registration_##x (void)                     \
    __attribute__((__constructor__))                                    \
{                                                                       \
    vlib_main_t * vm = vlib_get_main();                                 \
    x.next_registration = vm->node_main.node_registrations;             \
    vm->node_main.node_registrations = &x;                              \
}                                                                       \
__VA_ARGS__ vlib_node_registration_t x

int main()
{

    return 0;
}

#elif 1
template <typename... Args>
void print_callback(Args... args) {
    ((std::cout << args << " "), ...);
    std::cout << std::endl;
}
int main() {
    int x = 10;
    double y = 3.14;
    const char* str = "Hello, world!";
    print_callback(x, y, str);
    return 0;
}

#elif 1
typedef void (*CallbackFunc)(int);
void print_callback(int num) {  
    printf("%d\n",num);  
}
int main() {  
    int x = 10;
    CallbackFunc callback = print_callback;
    callback(x);
    return 0;  
}
#endif