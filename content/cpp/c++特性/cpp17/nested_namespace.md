```
#include <iostream>
using namespace std;
/*
namespace A {
    namespace B {
        namespace C {
            void func();
        }
    }
}
*/
// c++17，更方便更舒适
namespace A::B::C {
    void func(){cout<<"f"<<endl;};
}
int main()
{
    A::B::C::func();
}
```
命名空间嵌套