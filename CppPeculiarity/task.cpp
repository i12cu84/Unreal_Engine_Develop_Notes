#include <regex>
#include <string>
#include <iostream>
using namespace std;
#if 1

#include<stdio.h>
//#include<stdlib.h>
#include<stdarg.h>//ANSI C可变参数的头文件

int print(char* format, ...) {
    va_list ap;
    int n;
    va_start(ap, format);
    n = vprintf(format, ap);
    va_end(ap);
    return 0;
}

int main() {
    int ch1 = 10, ch2 = 20;
    print("%d\t%d\n%d\n", ch1, ch2, ch2);
    return 0;
}

#elif 1

#include <stdarg.h>  
#include <stdio.h>

void custom_printf(const char *format, ...) {  
    va_list args;  
    va_start(args, format);

    int i;  
    for (i = 0; format[i] != '\0'; i++) {  
        if (format[i] == '%') {  
            switch (format[i + 1]) {  
                case 'd': {  
                    int num = va_arg(args, int);  
                    printf("%d", num);  
                    break;  
                }  
                case 'f': {  
                    float num = va_arg(args, float);  
                    printf("%.2f", num);  
                    break;  
                }  
                case 's': {  
                    const char *str = va_arg(args, const char *);  
                    printf("%s", str);  
                    break;  
                }  
                default:  
                    printf("Invalid format specifier\n");  
                    break;  
            }  
        } else {  
            printf("%c", format[i]);  
        }  
    }

    va_end(args);  
}

int main() {  
    custom_printf("Hello, %s!\n", "World");  
    custom_printf("Number: %d\n", 42);  
    custom_printf("Pi: %.2f\n", 3.141592653589793);

    return 0;  
}

#elif 1
#include <stdio.h>

#define MY_VAR my_var

#define DEFINE_MY_VAR(var, num) int var ## num

int main() {
    DEFINE_MY_VAR(my_var, 1);
    printf("my_var1 = %d\n", my_var1);
    return 0;
}

#elif 1
#include <iostream>
#include <functional>

template <typename T>
T adds(T a)
{
    return a;
}

template <typename T, typename... arg>
T adds(T a, arg... args)
{
    return a + adds(args...);
}

int main()
{
    cout << "num: " << adds(3) << endl;
    cout << "num: " << adds(3, 4) << endl;
    cout << "num: " << adds(3, 4, 8) << endl;
    return 0;
}

#endif