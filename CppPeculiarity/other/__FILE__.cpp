#include <iostream>
using namespace std;
int main()
{
    char BuildFile[] = __FILE__;
    printf("编译文件路径：%s\n", BuildFile);
    return 0;
}