struct A {
    A(){}
    A(int a) { a_ = a; }
    A(int a, int b) : A(a) { b_ = b; }
/*
    A(int a, int b) { // 好麻烦
        a_ = a;
        b_ = b;
    }
*/
    int a_;
    int b_;
};
int main()
{
    return 0;
}