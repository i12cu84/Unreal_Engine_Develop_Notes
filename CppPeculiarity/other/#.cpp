#include <iostream>

// 定义字符串常量  

#define BODY_MACRO_COMBINE_INNER(A,B,C,D) A##B##C##D
#define BODY_MACRO_COMBINE(A,B,C,D) BODY_MACRO_COMBINE_INNER(A,B,C,D)

// 定义用于拼接字符串的宏  
#define CNT(a, b) a##b

int main()  
{
    // 输出拼接后的字符串  
   // std::cout << CNT("123","456") << std::endl;  
    auto str=  BODY_MACRO_COMBINE("123","456","123","456");  
    std::cout << str << std::endl;
    return 0;  
}
