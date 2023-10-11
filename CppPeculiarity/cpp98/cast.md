**Cast Operators**: C++98引入了四种新的类型转换操作符：`static_cast`、`dynamic_cast`、`const_cast`和`reinterpret_cast`。

```cpp
int main() {
    double d = 3.14;
    int i = static_cast<int>(d);
    return 0;
}
```

```
#include <iostream>
using namespace std;
int main()
{
    int a;
    const int &b = a;
    int &c = const_cast<int &>(b);
    cout << a << " " << b << " " << c << endl;
    // 0 0 0
    a = 1;
    cout << a << " " << b << " " << c << endl;
    // 1 1 1
    const_cast<int &>(b) = 2;
    cout << a << " " << b << " " << c << endl;
    // 2 2 2
    c = 3;
    cout << a << " " << b << " " << c << endl;
    // 3 3 3
    return 0;
}
```

```
#include <iostream>
#include <exception>
using namespace std;
class AClass{
  virtual void dummy() {}
};
class BClass : public AClass{
public:
  int a;
};
int main(){
  try  {
    AClass *abc = new BClass;
    AClass *aac = new AClass;
    BClass *bc;
    bc = dynamic_cast<BClass *>(abc);
    if (bc == nullptr)
      cout << "1" << endl;
    // null
    bc = dynamic_cast<BClass *>(aac); // will null
    if (bc == nullptr)
      cout << "2" << endl;
    // 2
  }
  catch (exception &e)
  {
    cout << "Exception: " << e.what();
  }
  return 0;
}
```

```
#include <iostream>
using namespace std;
int main()
{
     int num = 0x00636261; // 用16进制表示32位int，0x61是字符'a'的ASCII码
     int *pnum = &num;
     char *pstr = reinterpret_cast<char *>(pnum);
     cout << pnum << " " << *pnum << endl
          << static_cast<void *>(pstr) << " " << pstr << endl;
     // 0x45639ffd24 6513249
     // 0x45639ffd24 abc
     bool b1 = 1;
     int a = 196;
     bool b2 = *reinterpret_cast<bool *>(&a);
     cout << (b1 == b2) << endl
          << int(b1) << " " << b1 << endl
          << int(b2) << " " << b2 << endl;
     // 0
     // 1 1
     // 196 196
     unsigned int b = reinterpret_cast<unsigned int &>(a);
     cout << a << " " << b << endl;
     // 196 196
     return 0;
}
```

```
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
```