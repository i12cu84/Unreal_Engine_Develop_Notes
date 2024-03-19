```
#include <iostream>
#include <vector>
using namespace std;
int main(){
    //pair<int, double> n(1, 2.2); // before c++17
    pair n(1,1.1);
    cout<<n.first<<" "<<n.second<<endl;
    //vector<int> v={1,2,3};
    vector v={1,2,3};
    cout<<v[0]<<" "<<v[1]<<" "<<v[2]<<endl;
    //but had error: vector v2={1.1,2.2,3.3};
    return 0;
}
```
不需要特殊指定，直接可以推导出类型(但特定情况下会出错)