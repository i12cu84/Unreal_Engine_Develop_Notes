UMETA 宏在 Unreal Engine 中用于为类、属性或函数添加元数据。元数据是一组附加的信息，可以在蓝图、编辑器和编译器中使用。UMETA 宏的主要用途是提高代码的可读性和可维护性。
以下是一个使用 UMETA 宏的例子：
```
// 声明一个名为 "MyClass" 的类
USTRUCT(MyClass)
class MYGAME_API AMyClass : public AActor
{
    GENERATED_BODY()
public:
    // 添加一个名为 "MyProperty" 的 UPROPERTY
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyProperties")
    float MyProperty;
    // 使用 UMETA 为 MyProperty 添加元数据
    UMETA(DisplayName = "My Property")
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyProperties")
    float MyProperty;
    // 添加一个名为 "MyFunction" 的 UFUNCTION
    UFUNCTION(BlueprintCallable, Category = "MyFunctions")
    void MyFunction();
protected:
    // 使用 UMETA 添加一段描述
    UMETA(Description = "This is a description for MyClass")
    AMyClass();
};
```
在这个例子中，我们为 "MyProperty" 添加了 DisplayName 元数据，以便在编辑器中显示一个友好的名称。同时，我们还为 "MyClass" 添加了 Description 元数据，以便在编辑器中显示类的一个描述。
要在蓝图中使用这些元数据，您可以使用以下方法：
```
// 获取 "MyProperty" 的值
float MyPropertyValue = GetFloatProperty("MyProperty", NAME_MyProperty);
// 调用 "MyFunction" 函数
ExecuteUFunction(MyClass, FName(TEXT("MyFunction")), NAME_MyFunction);
```
在这些例子中，NAME_MyProperty 和 NAME_MyFunction 是在蓝图中定义的名称，用于引用代码中的属性和服务。通过在蓝图中使用这些名称，您可以轻松地访问和操作代码中的数据和功能。