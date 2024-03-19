C++98中引入了四种类型转换运算符：static_cast、dynamic_cast、const_cast和reinterpret_cast。这些运算符在编译器和运行时用于转换类型，各有不同的用途和安全性。

static_cast： static_cast主要用于数值类型之间的转换，例如int到float。它也可以用于类指针之间的转换。但是，在父类到子类的转换中，static_cast没有进行类型检查，因此在安全性方面较差。如果需要进行基类指针到派生类指针的转换，建议使用dynamic_cast（前提是派生类具有至少一个虚函数）。

dynamic_cast： dynamic_cast用于指针或引用操作，可以在运行时检查转换是否类型安全。它主要用于基类指针到派生类指针的转换，以确保多态性。dynamic_cast在转换前会检查指针（或引用）所指向对象的实际类型是否与转换的目的类型兼容。如果兼容，转换会发生；否则，会得到一个nullptr。dynamic_cast在安全性方面较好，但性能相对较低。

const_cast： const_cast用于去除指针或引用的 const 限制。它可以将const指针转换为非const指针，或将非const指针转换为const指针。const_cast还可以用于不同类型的指针之间的一致性转换，例如将基类指针转换为派生类指针（但请注意，这可能导致未定义行为，如果派生类不包含基类的所有成员）。

reinterpret_cast： reinterpret_cast用于将特定物理内存地址赋值给指针。它还可以在不同数据类型之间进行转换，例如将int转换为float。reinterpret_cast在低级编程和硬件接口开发中很有用。然而，使用reinterpret_cast进行指针转换可能导致未定义行为，因为它不进行任何类型检查。因此，在使用reinterpret_cast时，请确保目标类型与原始类型兼容。

总结：
    static_cast用于数值类型转换和基类指针到派生类指针的转换，但安全性较差。
    dynamic_cast用于运行时类型检查和多态性操作，安全性较好，但性能较低。
    const_cast用于去除指针或引用的const限制，以及进行一致性转换。
    reinterpret_cast用于低级编程和硬件接口开发，但可能导致未定义行为，需谨慎使用。

```
#if 1
//static_cast
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

#elif 1
//rinterpret_cast
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

#elif 1
//dynamic_cast
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

#elif 1
//const_cast
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

#endif
```