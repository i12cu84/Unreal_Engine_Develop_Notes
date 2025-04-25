# 第一轮报错

```cpp
1>[Adaptive Build] Excluded from TP unity file: TP.cpp, TPCommands.cpp, TPStyle.cpp
1>Determining max actions to execute in parallel (16 physical cores, 24 logical cores)
1>  Executing up to 16 processes, one per physical core
1>Using Unreal Build Accelerator local executor to run 8 action(s)
1>  Storage capacity 40Gb
1>---- Starting trace: 250418_102553_vs31952 ----
1>UbaSessionServer - Disable remote execution (remote sessions will finish current processes)
1>------ Building 8 action(s) started ------
1>[1/8] Compile [x64] TP.cpp
1>C:\Users\chru\Desktop\VRGK55\Plugins\TP\Source\TP\Private\TP.cpp(13): fatal error C1083: 无法打开包括文件: “../LevelEditor/Public/LevelEditorActions.h”: No such file or directory
1>[2/8] Compile [x64] Module.FileOperations.cpp
1>Trace file written to C:/Users/chru/AppData/Local/UnrealBuildTool/Log.uba with size 3.2kb
1>Total time in Unreal Build Accelerator local executor: 1.41 seconds
1>Total execution time: 2.93 seconds
1>C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Microsoft\VC\v170\Microsoft.MakeFile.Targets(44,5): error MSB3073: 命令“"C:\Program File\Epic Games\UE_5.5\Engine\Build\BatchFiles\Build.bat" VRGK2_427Editor Win64 DebugGame -Project="C:\Users\chru\Desktop\VRGK55\VRGK2_427.uproject" -WaitMutex -FromMsBuild -architecture=x64”已退出，代码为 6。
```

## 模块依赖问题

打开TP插件的构建配置文件：

VRGK55/Plugins/TP/Source/TP/TP.Build.cs

在PublicDependencyModuleNames或PrivateDependencyModuleNames中添加对LevelEditor模块的依赖（注意这是编辑器模块）：
```
if (Target.Type == TargetType.Editor)
{
    PrivateDependencyModuleNames.AddRange(new string[] { 
        "LevelEditor" 
    });
}
```
修改包含路径：
```
将#include "../LevelEditor/Public/LevelEditorActions.h"
```
改为引擎标准路径格式：
```
#include "LevelEditor/LevelEditorActions.h"
```

## 验证插件启用状态

在项目根目录的VRGK2_427.uproject文件上右键，选择"Generate Visual Studio Project Files"重新生成解决方案。

双击VRGK2_427.uproject启动Unreal Editor，进入Edit > Plugins：

在"Built-in"分类下启用"Media Framework"相关插件

确保所有自定义插件（TP/FileOperations）已启用

最后,清理并重新构建

# 第二轮报错

```cpp
1>[1/8] Compile [x64] TP.cpp
1>C:\Users\chru\Desktop\VRGK55\Plugins\TP\Source\TP\Private\TP.cpp(14): fatal error C1083: 无法打开包括文件: “LevelEditor/LevelEditorActions.h”: No such file or directory
1>C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Microsoft\VC\v170\Microsoft.MakeFile.Targets(44,5): error MSB3073: 命令“"C:\Program File\Epic Games\UE_5.5\Engine\Build\BatchFiles\Build.bat" VRGK2_427Editor Win64 DebugGame -Project="C:\Users\chru\Desktop\VRGK55\VRGK2_427.uproject" -WaitMutex -FromMsBuild -architecture=x64”已退出，代码为 6。
```

## LevelEditorActions.h路径问题修复

错误现象：
```
TP.cpp(14): fatal error C1083: 无法打开包括文件: “LevelEditor/LevelEditorActions.h”
```
原因分析：

UE5.5中LevelEditorActions.h可能已被迁移至EditorFramework模块

需要确认头文件的实际路径和模块依赖关系

解决方案：
验证头文件位置
在引擎目录中搜索该文件：
```
cd "C:\Program File\Epic Games\UE_5.5\Engine\Source"
dir LevelEditorActions.h /s
```
如果确认文件不存在，说明该头文件已废弃或被移动

更新代码引用方式
修改TP.cpp中的包含语句为：
```
#include "Framework/Commands/LevelEditorActions.h"
```
修改构建依赖

更新TP.Build.cs：
```
PrivateDependencyModuleNames.AddRange(new string[] {
    "EditorFramework",    // 新增
    "AssetTools",        // 新增
    "LevelEditor"
});
```
