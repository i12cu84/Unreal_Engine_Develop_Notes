#include <iostream>
#include <string>
#include <cstring>//strlen
using namespace std;
int main()
{
    string str="hello";
    cout << sizeof(int) << endl;
    cout << sizeof(str) << endl;
    cout << strlen("Hello") << endl;
}

/*
sizeof()：
sizeof() 是一个运算符，用于计算变量或类型所占用的内存字节数。
可以用于任何类型的数据，包括基本数据类型、数组、结构体等。
计算的是变量或类型的大小，包括字节数。
示例：
int x;
printf("sizeof(int) = %lu\n", sizeof(int)); // 输出 4，即整型变量占用 4 个字节

strlen()：
strlen() 是一个函数，用于计算以空字符 '\0' 结尾的字符串的长度。
只能用于字符串，计算的是字符串中字符的个数，不包括字符串末尾的空字符。
示例：
char s[] = "Hello, world!";
printf("strlen(s) = %lu\n", strlen(s)); // 输出 13，即字符串 s 中有 13 个字符（不包括结尾的空字符 '\0'）

总结：
sizeof() 计算的是变量或类型的字节数，适用于任何数据类型。
strlen() 计算的是字符串的长度，只适用于以空字符结尾的字符串。
*/