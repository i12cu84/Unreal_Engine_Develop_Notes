**Template Instantiations and Member Templates**: C++98支持模板实例化和成员模板。

```cpp
template<typename T>
class MyClass {
public:
    T data;
};

int main() {
    MyClass<int> obj;
    obj.data = 10;
    return 0;
}
```