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