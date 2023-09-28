```
struct Base {
    Base() {}
    Base(int a) { a_ = a; }
    int a_;
};
struct Derived : Base {
    using Base::Base;
/*
    Derived() {}
    Derived(int a) : Base(a) {} // 好麻烦
*/
};
int main() {
    Derived a(1);
    return 0;
}
```
继承构造函数可以让派生类直接使用基类的构造函数，如果有一个派生类，我们希望派生类采用和基类一样的构造方式，可以直接使用基类的构造函数，而不是再重新写一遍构造函数