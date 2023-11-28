Unreal Engine 中的 RIGVM_METHOD 宏主要用于实现蓝图（Blueprint）中的虚拟机方法（VM Methods）。虚拟机方法是在蓝图中运行的 C++ 代码，可以让我们更好地控制蓝图的行为。RIGVM_METHOD 宏用于定义虚拟机方法的接口。
以下是使用 RIGVM_METHOD 宏的基本步骤：
声明虚拟机方法：在头文件（.h）中，使用 RIGVM_METHOD 宏声明虚拟机方法。例如：
```
// MyClass.h
class MyClass : public UObject
{
public:
    RIGVM_METHOD(MyClass, MyMethodName)
    // 其他方法...
};
```
定义虚拟机方法的参数：在头文件中，使用 RIGVM_PARAM 宏定义虚拟机方法的参数。例如：
```
// MyClass.h
class MyClass : public UObject
{
public:
    RIGVM_METHOD(MyClass, MyMethodName)
    RIGVM_PARAM(FString, InStringParam)
    RIGVM_PARAM(int32, InIntParam)
    // 其他方法...
};
```
实现虚拟机方法：在源文件（.cpp）中，实现虚拟机方法。例如：
```
// MyClass.cpp
#include "MyClass.h"
UCLASS()
class MYGAME_API AMyClass : public UObject
{
    GENERATED_BODY()
public:
    virtual void MyMethodName(const FString& InStringParam, int32 InIntParam)
    {
        // 在这里实现虚拟机方法的功能
    }
};
```
在蓝图中调用虚拟机方法：在蓝图编辑器中，拖动实现虚拟机方法的节点到其他节点，从而实现蓝图之间的连线。例如，将 MyMethodName 节点拖到另一个节点上，如下所示：
```
            +-----------------------------------------------------------------+
            |                                                               |
            |   MyMethodName(InStringParam, InIntParam)                  |
            |                                                               |
            +-----------------------------------------------------------------+
```
然后，在对应的参数槽中输入所需的数据，如字符串和整数。
通过以上步骤，您可以在 Unreal Engine 中使用 RIGVM_METHOD 宏实现虚拟机方法，从而更好地控制蓝图的行为。