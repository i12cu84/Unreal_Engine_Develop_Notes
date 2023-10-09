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