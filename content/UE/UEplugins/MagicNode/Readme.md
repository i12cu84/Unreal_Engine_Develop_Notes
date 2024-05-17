
功能解析:

在蓝图中绘制c++代码并且支持c++蓝图节点热编译

环境搭建:

Epic Game 商城中下载"MagicNodeRuntime"插件并添加到目标版本工程中

创建UE项目后(注意要C++工程)

UE左上角 编辑 -> 插件 -> 搜索 "MagicNodeRuntime" -> 启用

关闭UE -> sln打开工程 -> 解决方案资源管理器 -> Games -> [项目名] -> Source -> [项目名].Build.cs 打开

PublicDependencyModuleNames.AddRange -> 需要将"MagicNodeRuntime"模块包含在其中

例如以下代码

```
// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MNTask : ModuleRules
{
    public MNTask(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "MagicNodeRuntime" });//添加了"MagicNodeRuntime"
    }
}

```

编译运行即可

启用方式:

蓝图节点拉出后 -> Magic Node 呼出蓝图节点使用


具体使用方法解析:https://brunoxavierleite.com/2019/01/16/unreal-magic-nodes-programming/

解决与提交该插件问题论坛:https://forums.unrealengine.com/t/magic-nodes/121220/42


1.始终必须使用“IMGC”宏声明标头
此宏将调用 UFUNCTION（） 宏，并为 Execute 条目配置默认设置，以便可由蓝图调用。如果将 Asset Browser 的 View Options 配置为显示插件内容，则可以找到一些示例，例如以下打印节点

.H
```
public:
IMGC() static void Execute (
    UObject* Context,
    const TArray<FString> &Array
);
```
.CPP
```
void FSelf::Execute (
    UObject* Context,
    const TArray<FString> &Array
) {
    for (auto &Item : Array) {
        LOG_MGC(Item);
        LOG_MGC(1.0f,FColor::Blue,Item);
    }
}
```
如果不声明标头，则虚拟机将不可见函数

2.输入引脚
虚幻引擎会检查输入是否为 const、是否为 value 或引用类型等。
例如，这将是一个数组作为输入引用：

```
IMGC() static void Execute (
	const TArray<FString> &ArrayIN
    //另外 TArray<FString> ArrayIN 也可以
)
```

虽然这将是一个以数组作为输出引脚的节点：

```
IMGC() static void Execute (
	TArray<FString> & ArrayOut
)
```
注意：

请记住，这是说明性的，节点的每个 Execute（） 函数都必须包含一个
UObject* Context