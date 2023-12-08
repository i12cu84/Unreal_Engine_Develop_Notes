//代码有问题 未知原因

#include <stdio.h>

#define MY_VAR my_var

#define DEFINE_MY_VAR(var, num) int var ## num

int main() {
    DEFINE_MY_VAR(my_var, 1);
    printf("my_var1 = %d\n", my_var1);
    return 0;
}

