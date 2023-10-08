```
template<typename T, typename U>
struct A 
{
    T t;
    U u;
};
template<typename T>
using B = A<T, int>;
int main() 
{
    B<double> b;
    b.t = 10;
    b.u = 20;
    cout << b.t << endl;
    cout << b.u << endl;
    return 0;
}
```
模板类别名