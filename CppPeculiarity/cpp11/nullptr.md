```
void func(void *ptr) 
{
    cout << "func ptr" << endl;
}
void func(int i) 
{
    cout << "func i" << endl;
}
int main() {
    func(NULL); // 编译失败，会产生二义性
    func(nullptr); // 输出func ptr
    return 0;
}
```
nullptr是用来表示空指针新引入的常量值，在c++中如果表示空指针语义时建议使用nullptr而不要使用NULL，因为NULL本质上是个int型的0，其实不是个指针。