UPARAM 宏在 Unreal Engine 中用于声明函数的参数。这个宏使得在蓝图中调用函数时，可以更方便地访问和操作参数。使用 UPARAM 宏可以提高代码的可读性和一致性。
以下是一个使用 UPARAM 宏的例子：
```
// 声明一个名为 "MyFunction" 的 UFUNCTION
UFUNCTION(BlueprintCallable, Category = "MyFunctions")
void MyFunction(
    // 添加一个名为 "FloatParam" 的 UPROPERTY
    UPARAM(DisplayName = "Float Parameter", Category = "MyParameters")
    float FloatParam,
    // 添加一个名为 "IntParam" 的 UPROPERTY
    UPARAM(DisplayName = "Int Parameter", Category = "MyParameters")
    int IntParam
);
```
在这个例子中，我们为 "MyFunction" 函数添加了两个参数：FloatParam 和 IntParam。我们还使用了 DisplayName 参数为这些参数添加了友好的名称，并在蓝图中显示。
要在蓝图中调用这个函数并传递参数，您可以使用以下方法：
```
// 声明一个名为 "MyFunction" 的 UFUNCTION
UFUNCTION(BlueprintCallable, Category = "MyFunctions")
void MyFunction(
    UPARAM(FloatParam, FloatParam),
    UPARAM(IntParam, IntParam)
);
// 调用 "MyFunction" 函数，并传递参数
MyFunction(1.5f, 42);
```
在这个例子中，我们通过在蓝图中调用 MyFunction 函数并传递 FloatParam 和 IntParam 参数，来实现函数的功能。由于我们在代码中使用了 UPARAM 宏，因此在蓝图中调用这个函数时，参数的名称和分类将保持一致。
请注意，您还可以使用 BlueprintReadOnly、VisibleAnywhere 和其他相关宏来设置属性的其他特性。这有助于确保在蓝图和代码中的一致性。