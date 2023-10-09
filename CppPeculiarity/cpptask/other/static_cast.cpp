#include <iostream>
#include <vector>
using namespace std;
struct B
{
    int m = 42;
    const char *fun() const { return "fun1"; }
};
struct D : B
{
    const char *fun() const { return "fun2"; }
};
int main()
{
    // 用于原C风格的隐式类型转换
    {
        float a = 1.3;
        int b = static_cast<int>(a);
        cout << "b=" << b << endl;
        // b=1
    }
    // 静态下行转换
    {
        D d;
        B &br = d;
        cout << br.fun() << endl;
        // fun1
        D &another_d = static_cast<D &>(br);
        cout << another_d.fun() << endl;
        // fun2
    }
    // 左值转换为右值引用
    {
        vector<int> v0{1, 2, 3};
        cout << v0.size() << endl;
        // 3
        vector<int> v2 = static_cast<vector<int> &&>(v0);
        cout << v0.size() << endl;
        // 0
    }
    // 初始化转换
    {
        int n = static_cast<int>(3.14);
        cout << n << endl;
        // 3
        vector<int> v = static_cast<vector<int>>(10);
        cout << v.size() << endl;
        // 10
    }
    //// 转换为void并丢弃
    //{
    //    vector<int> v2(2);
    //    static_cast<void>(v2.size());
    //    // int a =  static_cast<void>(v2.size());  //error,void value not ignored as it ought to be
    //}
    // 上行转换，同时将数组转换为指针
    {
        D a[10];
        cout << a->fun() << endl;
        // fun2
        B *dp = static_cast<B *>(a);
        cout << dp->fun() << endl;
        // fun1
    }
    // void*转换到具体类型
    {
        int n = static_cast<int>(3.14);
        void *nv = &n;
        int *ni = static_cast<int *>(nv);
        cout << *ni << endl;
        // 3
    }
    // 枚举转int
    {
        enum class E
        {
            ONE = 1,
            TWO,
            THREE
        };
        E e = E::TWO;
        int two = static_cast<int>(e);
        cout << two << endl;
        // 2
    }
    // int转enum以及enum转为其他enum
    {
        enum class E
        {
            ONE = 1,
            TWO,
            THREE
        };
        enum EU
        {
            ONE = 1,
            TWO,
            THREE
        };
        E e2 = static_cast<E>(TWO);
        EU eu = static_cast<EU>(e2);
        cout << static_cast<int>(e2) << " " << static_cast<int>(eu) << endl;
        // 2 2
    }
    // 成员指针的上行转换
    {
        D d;
        B &br = d; // upcast via implicit conversion
        int D::*pm = &D::m;
        cout << br.*static_cast<int B::*>(pm) << endl;
        // 42
    }
    return 0;
}
