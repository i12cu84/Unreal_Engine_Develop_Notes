//用于测试define用法
#include <iostream>
using namespace std;
#define Define_Class(_name,_print,_int)\
class _name{\
public:\
    _name(int _a):_int(_a){}\
    int _int;\
    void _print(){cout<<_int<<endl;}\
};

class text{
    text(int _a):_int(_a){}\
    int _int;\
    void _print(){cout<<_int<<endl;}\
};

#define Inherit_Class(_nname,_parent)\
class _nname: public _parent{\
    void _pritn_more(){\
        cout<<"1"<<endl;\
    }\
};

int main()
{
    Define_Class(MyClass, print, data);
    MyClass myObject(123);
    myObject.print();

    Inherit_Class(SonClass,MyClass);
    // SonCloass
    return 0;
}