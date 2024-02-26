#include <iostream>
using namespace std;
// 定义一个标识符
#define DEF_INT int
int main() {
    // 检查 DEF_INT 是否已定义
    #if defined(DEF_INT)
        DEF_INT i=10;
        cout << "DEF_INT 已定义" << i<<endl;
    #else
        cout << "DEF_INT 未定义" << endl;
    #endif
    return 0;
}