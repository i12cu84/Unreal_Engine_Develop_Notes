```
#include <iostream>
#include <tuple>
using namespace std;
tuple<int,double,string> fun(){
    return make_tuple(10,2.5,"hello");
}
int main(){
    auto [a,b,c] = fun();
    cout<<a<<" "<<b<<" "<<c<<endl;
    // 10 2.5 hello
    cout<<get<0>(fun())<<endl;
    // 10
    return 0;
}
```
tuple即元组，可以理解为pair的扩展，可以用来将不同类型的元素存放在一起，常用于函数的多返回值。