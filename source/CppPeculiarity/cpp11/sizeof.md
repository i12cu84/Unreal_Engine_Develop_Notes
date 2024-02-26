```
struct A 
{
    int data[10];
    int a;
};
int main() 
{
    cout << "size " << sizeof(A::data) << endl;
    return 0;
}
```
sizeof可以计算class的大小