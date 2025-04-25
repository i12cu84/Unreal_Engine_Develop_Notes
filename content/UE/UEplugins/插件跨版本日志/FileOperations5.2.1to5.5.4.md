# 第一轮报错

```cpp
1>[Adaptive Build] Excluded from FileOperations unity file: FileOperations.cpp, FileOperationsBPLibrary.cpp
1>[2/8] Compile [x64] Module.FileOperations.cpp
1>C:\Users\chru\Desktop\VRGK55\Plugins\FileOperations\Source\FileOperations\Public\FileOperationsBPLibrary.h(30): fatal error C1083: 无法打开包括文件: “MediaAssets/Public/FileMediaSource.h”: No such file or directory
1>[3/8] Compile [x64] FileOperationsBPLibrary.cpp
1>C:\Users\chru\Desktop\VRGK55\Plugins\FileOperations\Source\FileOperations\Public\FileOperationsBPLibrary.h(30): fatal error C1083: 无法打开包括文件: “MediaAssets/Public/FileMediaSource.h”: No such file or directory
1>Trace file written to C:/Users/chru/AppData/Local/UnrealBuildTool/Log.uba with size 3.2kb
1>Total time in Unreal Build Accelerator local executor: 1.41 seconds
1>Total execution time: 2.93 seconds
1>C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Microsoft\VC\v170\Microsoft.MakeFile.Targets(44,5): error MSB3073: 命令“"C:\Program File\Epic Games\UE_5.5\Engine\Build\BatchFiles\Build.bat" VRGK2_427Editor Win64 DebugGame -Project="C:\Users\chru\Desktop\VRGK55\VRGK2_427.uproject" -WaitMutex -FromMsBuild -architecture=x64”已退出，代码为 6。
```

## 修复FileMediaSource.h缺失问题

打开FileOperations插件的构建配置文件：
```
VRGK55/Plugins/FileOperations/Source/FileOperations/FileOperations.Build.cs
```

添加对MediaAssets模块的依赖：
```
PublicDependencyModuleNames.AddRange(new string[] { 
    "MediaAssets" 
});
```
修改包含路径：
```
将#include "MediaAssets/Public/FileMediaSource.h"
```
改为引擎标准路径格式：
```
#include "FileMediaSource.h"
```

## 验证插件启用状态

在项目根目录的VRGK2_427.uproject文件上右键，选择"Generate Visual Studio Project Files"重新生成解决方案。

双击VRGK2_427.uproject启动Unreal Editor，进入Edit > Plugins：

在"Built-in"分类下启用"Media Framework"相关插件

确保所有自定义插件（TP/FileOperations）已启用

最后,清理并重新构建

# 第二轮报错

```cpp
1>[2/8] Compile [x64] FileOperationsBPLibrary.cpp
1>C:\Users\chru\Desktop\VRGK55\Plugins\FileOperations\Source\FileOperations\Public\FileOperationsBPLibrary.h(171): error C2039: "ClipboardCopy": 不是 "FWindowsPlatformMisc" 的成员
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\Core\Public\Windows\WindowsPlatformMisc.h(96): note: 参见“FWindowsPlatformMisc”的声明
1>C:\Users\chru\Desktop\VRGK55\Plugins\FileOperations\Source\FileOperations\Public\FileOperationsBPLibrary.h(171): error C3861: “ClipboardCopy”: 找不到标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\FileOperations\Source\FileOperations\Public\FileOperationsBPLibrary.h(178): error C2039: "ClipboardPaste": 不是 "FWindowsPlatformMisc" 的成员
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\Core\Public\Windows\WindowsPlatformMisc.h(96): note: 参见“FWindowsPlatformMisc”的声明
1>C:\Users\chru\Desktop\VRGK55\Plugins\FileOperations\Source\FileOperations\Public\FileOperationsBPLibrary.h(178): error C3861: “ClipboardPaste”: 找不到标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\FileOperations\Source\FileOperations\Public\FileOperationsBPLibrary.h(400): error C2039: "PlatformData": 不是 "UTexture2D" 的成员
1>C:\Users\chru\Desktop\VRGK55\Plugins\FileOperations\Intermediate\Build\Win64\UnrealEditor\Inc\FileOperations\UHT\FileOperationsBPLibrary.generated.h(15): note: 参见“UTexture2D”的声明
1>C:\Users\chru\Desktop\VRGK55\Plugins\FileOperations\Source\FileOperations\Public\FileOperationsBPLibrary.h(403): error C2039: "PlatformData": 不是 "UTexture2D" 的成员
1>C:\Users\chru\Desktop\VRGK55\Plugins\FileOperations\Intermediate\Build\Win64\UnrealEditor\Inc\FileOperations\UHT\FileOperationsBPLibrary.generated.h(15): note: 参见“UTexture2D”的声明
1>[3/8] Compile [x64] Module.FileOperations.cpp
1>C:\Users\chru\Desktop\VRGK55\Plugins\FileOperations\Source\FileOperations\Public\FileOperationsBPLibrary.h(171): error C2039: "ClipboardCopy": 不是 "FWindowsPlatformMisc" 的成员
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\Core\Public\Windows\WindowsPlatformMisc.h(96): note: 参见“FWindowsPlatformMisc”的声明
1>C:\Users\chru\Desktop\VRGK55\Plugins\FileOperations\Source\FileOperations\Public\FileOperationsBPLibrary.h(171): error C3861: “ClipboardCopy”: 找不到标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\FileOperations\Source\FileOperations\Public\FileOperationsBPLibrary.h(178): error C2039: "ClipboardPaste": 不是 "FWindowsPlatformMisc" 的成员
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\Core\Public\Windows\WindowsPlatformMisc.h(96): note: 参见“FWindowsPlatformMisc”的声明
1>C:\Users\chru\Desktop\VRGK55\Plugins\FileOperations\Source\FileOperations\Public\FileOperationsBPLibrary.h(178): error C3861: “ClipboardPaste”: 找不到标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\FileOperations\Source\FileOperations\Public\FileOperationsBPLibrary.h(400): error C2039: "PlatformData": 不是 "UTexture2D" 的成员
1>C:\Users\chru\Desktop\VRGK55\Plugins\FileOperations\Intermediate\Build\Win64\UnrealEditor\Inc\FileOperations\UHT\FileOperationsBPLibrary.generated.h(15): note: 参见“UTexture2D”的声明
1>C:\Users\chru\Desktop\VRGK55\Plugins\FileOperations\Source\FileOperations\Public\FileOperationsBPLibrary.h(403): error C2039: "PlatformData": 不是 "UTexture2D" 的成员
1>C:\Users\chru\Desktop\VRGK55\Plugins\FileOperations\Intermediate\Build\Win64\UnrealEditor\Inc\FileOperations\UHT\FileOperationsBPLibrary.generated.h(15): note: 参见“UTexture2D”的声明
1>Total execution time: 3.03 seconds
1>C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Microsoft\VC\v170\Microsoft.MakeFile.Targets(44,5): error MSB3073: 命令“"C:\Program File\Epic Games\UE_5.5\Engine\Build\BatchFiles\Build.bat" VRGK2_427Editor Win64 DebugGame -Project="C:\Users\chru\Desktop\VRGK55\VRGK2_427.uproject" -WaitMutex -FromMsBuild -architecture=x64”已退出，代码为 6。
```

## 剪贴板API更新

错误现象：
```
FileOperationsBPLibrary.h(171): error C2039: "ClipboardCopy": 不是 "FWindowsPlatformMisc" 的成员
```
原因分析：
UE5.5已将剪贴板API迁移

修改为如下代码
```
// 需要包含的头文件
#include "Misc/App.h"
#include "Misc/PlatformProperties.h"
#include "HAL/PlatformApplicationMisc.h" // 核心剪贴板API所在
#include "HAL/Platform.h"

// 复制功能
UFUNCTION(BlueprintCallable, Category = "Clipboard")
static void CopyMessageToClipboard(FString Text)
{
    // 直接使用平台级API（线程安全版本）
    FPlatformApplicationMisc::ClipboardCopy(*Text);
}

// 粘贴功能
UFUNCTION(BlueprintCallable, Category = "Clipboard")
static FString PasteMessageFromClipboard()
{
    FString ClipboardContent;
    // 增强型粘贴接口
    FPlatformApplicationMisc::ClipboardPaste(ClipboardContent);
    return ClipboardContent;
}
```
FileOperations的 Build.cs 文件修改
```
PublicDependencyModuleNames.AddRange(
    new string[] {
        "Core",
        "ApplicationCore" // 必需的核心模块
    }
);
```

## UTexture2D::PlatformData访问问题

错误现象：
```
FileOperationsBPLibrary.h(400): error C2039: "PlatformData": 不是 "UTexture2D" 的成员
```
原因分析：

UE5.5中UTexture2D::PlatformData已改为受保护成员

需要通过专用接口访问纹理数据

解决方案：
修改数据访问方式
使用UE提供的标准API：
```
// 原问题代码示例
FTexturePlatformData* PlatformData = Texture->PlatformData;
// 修改为
#if WITH_EDITOR
FTexturePlatformData* PlatformData = Texture->GetPlatformData();
#else
FTexturePlatformData* PlatformData = Texture->GetPlatformData(); // 需要确认运行时可用性
#endif
```
添加必要的头文件包含
在FileOperationsBPLibrary.h顶部添加：
```
#include "Engine/Texture.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"  // 确保访问PlatformData所需
```