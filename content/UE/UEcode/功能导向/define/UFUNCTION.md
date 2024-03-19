UFUNCTION： 使用方法：
```
UFUNCTION(BlueprintCallable, Category = "MyFunctions");
用于声明一个可以在蓝图中调用的函数。BlueprintCallable 标志表示该函数可以在蓝图中调用。Category 参数表示函数的分类。
```

函数说明
BlueprintCallable(可在蓝图,关卡蓝图图表中执行)
BlueprintCosmetic(无法在专用服务器上运行)
BlueprintImplementableEvent(可在蓝图或关卡蓝图图表中实现)
Category(蓝图编辑工具中显示时指定函数的类别)    

具体细节:https://docs.unrealengine.com/4.27/zh-CN/ProgrammingAndScripting/GameplayArchitecture/Functions/