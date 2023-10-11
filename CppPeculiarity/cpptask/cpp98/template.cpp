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