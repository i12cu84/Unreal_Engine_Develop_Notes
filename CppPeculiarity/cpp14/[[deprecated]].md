```
struct [[deprecated]] A { };
int main() {
    A a;
    return 0;
}
```
编译时被产生警告，用户提示开发者该标记修饰的内容将来可能会被丢弃，尽量不要使用