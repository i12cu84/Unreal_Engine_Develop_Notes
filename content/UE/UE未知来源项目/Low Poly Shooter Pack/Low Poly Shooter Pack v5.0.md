引擎版本5.3 笔者只有5.5版本

1.Engine modules are out of date, and cannot be compiled while the engine is running. Please build through your IDE. //引擎模块过期，无法在引擎运行时进行编译。请通过您的IDE进行构建。

[解决方法](../../UEcode/架构/工程蓝图项目转为cpp项目.md)

---

2.Visual Studio 2022(后面以VS代替) 打开未响应
删除根目录".vs"文件

---

3.VS 2022 版本问题
```
C:\...\UE5.vcxproj : warning  : 无法找到 Visual Studio 2022 (v143) 的生成工具。安装 Visual Studio 2022 (v143) 可使用 Visual Studio 2022 (v143) 生成工具进行生成。
C:\...\UE5.vcxproj : warning  : 无法找到项目文件“UE5”中引用的平台“Win64”。
```
该装装 [官网](https://visualstudio.microsoft.com/zh-hans/vs/) or [Community直达](https://visualstudio.microsoft.com/zh-hans/thank-you-downloading-visual-studio/?sku=Community&channel=Release&version=VS2022&source=VSLandingPage&cid=2030&passive=false)
或是VS2022自行安装
```
适用于v143生成工具的C++ v14.38(17.8) ATL (x86 和 x64)
MSVC v143 - VS 2022 C++ x64/x86 生成工具 (v14.38-17.8)
```

---

4.编译出错,关键信息:
```
LPSPEditor modifies the values of properties: [ bStrictConformanceMode: False != True ]
This is not allowed, as LPSPEditor has build products in common with UnrealEditor.
```
项目目标文件（LPSPEditor.Target.cs）中的某些设置与引擎默认值冲突（如 bStrictConformanceMode 被修改），但未声明独立构建环境。

需在 LPSPEditor.Target.cs 中显式声明构建环境或放弃冲突设置,比如如下改动
```cpp
using UnrealBuildTool;
using System.Collections.Generic;

public class LPSPEditorTarget : TargetRules
{
    public LPSPEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;   // 强制使用UE5.5的构建设置
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5; // 更新包含顺序
        CppStandard = CppStandardVersion.Cpp20;          // 明确指定C++20标准

        // 解决方案1：声明使用独立构建环境
        //BuildEnvironment = TargetBuildEnvironment.Unique;

        // 或解决方案2：强制覆盖引擎默认设置（风险更高）
        bOverrideBuildEnvironment = true;

        ExtraModuleNames.AddRange(new[] { "LPSP" });
    }
}
```
