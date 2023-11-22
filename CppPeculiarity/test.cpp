#include <iostream>  
#include <functional>
using namespace std;
#if 0

#elif 1

#include <iostream>

int main() {  
    int a = 10;  
    std::cout << "The type of a is: " << typeof(a) << std::endl;  
    return 0;  
}

#elif 1

static void __vlib_add_node_registration_ (void)                     
    __attribute__((__constructor__))                                    
{                                                                       
    vlib_main_t * vm = vlib_get_main();                                 
    x.next_registration = vm->node_main.node_registrations;             
    vm->node_main.node_registrations = &x;                              
}                                                                       
__VA_ARGS__ vlib_node_registration_t x;

int main()
{
    return 0;
}

#elif 1

// 使用 define 定义一个常量，用于表示窗口大小  
#define WINDOW_SIZE 10

// 使用 define 定义一个静态成员函数  
#define STATIC_FUNCTION static

class Counter {  
public:  
    // 构造函数  
    Counter() {  
        count = 0;  
    }

    // 静态成员函数（使用 define 定义）  
    STATIC_FUNCTION void increment() {  
        count++;  
        std::cout << "Counter count: " << count << std::endl;  
    }

    // 普通成员函数，用于输出计数器值  
    void print() {  
        std::cout << "Counter count: " << count << std::endl;  
    }

private:  
    int count;  
};

int main() {  
    Counter counter;

    // 调用静态成员函数 increment  
    counter.increment();

    // 调用普通成员函数 print  
    counter.print();

    return 0;  
}



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
val3late <typename... Args>
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