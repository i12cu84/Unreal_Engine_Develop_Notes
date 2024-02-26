struct A 
{
    A() = default;
    A(const A&) = delete;
    A& operator=(const A&) = delete;
    int a;
    A(int i) { a = i; }
};
int main() 
{
    A a1;
    //A a2 = a1;  // 错误，拷贝构造函数被禁用
    A a3;
    //a3 = a1;  // 错误，拷贝赋值操作符被禁用
}