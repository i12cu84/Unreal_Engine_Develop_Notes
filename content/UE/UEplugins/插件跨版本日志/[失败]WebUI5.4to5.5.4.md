注意:最终没有解决问题,仅提供思路
<details>
<summary>无效内容折叠</summary>
<pre><code>

# 第一轮报错

注,非异常内容省去
```cpp
1>[3/174] Compile [x64] JsonLibraryConverter.cpp (0:01.23 at +0:00)
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(250): warning C4996: 'FProperty::ElementSize': Use GetElementSize/SetElementSize instead. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(269): error C2653: “UUserDefinedStruct”: 不是类或命名空间名称
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(269): error C2672: “StaticClass”: 未找到匹配的重载函数
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\ReflectedTypeAccessors.h(13): note: 可能是“UClass *StaticClass(void)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(269): note: “UClass *StaticClass(void)”: 无法推导“ClassType”的 模板 参数
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(269): error C2672: “UObjectBaseUtility::IsA”: 未找到匹配的重载函数
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\UObjectBaseUtility.h(623): note: 可能是“bool UObjectBaseUtility::IsA(void) const”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(269): note: “bool UObjectBaseUtility::IsA(void) const”: 应输入 0 个参数，却提供了 1 个
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\UObjectBaseUtility.h(602): note: 或    “bool UObjectBaseUtility::IsA(OtherClassType) const”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(946): warning C4996: 'FProperty::ElementSize': Use GetElementSize/SetElementSize instead. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(972): error C2653: “UUserDefinedStruct”: 不是类或命名空间名称
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(972): error C2672: “StaticClass”: 未找到匹配的重载函数
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\ReflectedTypeAccessors.h(13): note: 可能是“UClass *StaticClass(void)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(972): note: “UClass *StaticClass(void)”: 无法推导“ClassType”的 模板 参数
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(972): error C2672: “UObjectBaseUtility::IsA”: 未找到匹配的重载函数
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\UObjectBaseUtility.h(623): note: 可能是“bool UObjectBaseUtility::IsA(void) const”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(972): note: “bool UObjectBaseUtility::IsA(void) const”: 应输入 0 个参数，却提供了 1 个
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\UObjectBaseUtility.h(602): note: 或    “bool UObjectBaseUtility::IsA(OtherClassType) const”
1>
1>Error executing C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.38.33130\bin\Hostx64\x64\cl.exe (tool returned code: 2)
1>[131/174] Compile [x64] K2Node_JsonLibraryToStruct.cpp (0:04.62 at +2:35)
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(227): error C2065: “UUserDefinedStruct”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(227): error C2065: “UserStructType”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(227): error C2065: “UUserDefinedStruct”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(227): error C2672: “Cast”: 未找到匹配的重载函数
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\Linker.h(614): note: 可能是“T *Cast(FLinker *)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(227): note: “Cast”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h(411): note: 或    “const T *Cast(const U *)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(227): note: “Cast”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h(407): note: 或    “T *Cast(const TSubclassOf<U> &)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(227): note: “Cast”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h(295): note: 或    “TCopyQualifiersFromTo<From,To>::Type *Cast(const TObjectPtr<ValueType> &)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(227): note: “Cast”:“To”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h(289): note: 或    “T *Cast(const TWeakObjectPtr<UserClass,FWeakObjectPtr> &)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(227): note: “Cast”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\Core\Public\Delegates\DelegateSignatureImpl.inl(33): note: 或    “To *Cast(From *)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(227): note: “Cast”:“To”的 模板 参数无效，应为类型
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(230): error C2065: “UserStructType”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(230): error C2065: “UserStructType”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(231): error C2065: “UserStructType”: 未声明的标识符
1>
1>Error executing C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.38.33130\bin\Hostx64\x64\cl.exe (tool returned code: 2)
1>[133/174] Compile [x64] K2Node_JsonLibraryFromStruct.cpp (0:04.70 at +2:35)
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(227): error C2065: “UUserDefinedStruct”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(227): error C2065: “UserStructType”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(227): error C2065: “UUserDefinedStruct”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(227): error C2672: “Cast”: 未找到匹配的重载函数
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\Linker.h(614): note: 可能是“T *Cast(FLinker *)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(227): note: “Cast”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h(411): note: 或    “const T *Cast(const U *)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(227): note: “Cast”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h(407): note: 或    “T *Cast(const TSubclassOf<U> &)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(227): note: “Cast”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h(295): note: 或    “TCopyQualifiersFromTo<From,To>::Type *Cast(const TObjectPtr<ValueType> &)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(227): note: “Cast”:“To”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h(289): note: 或    “T *Cast(const TWeakObjectPtr<UserClass,FWeakObjectPtr> &)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(227): note: “Cast”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\Core\Public\Delegates\DelegateSignatureImpl.inl(33): note: 或    “To *Cast(From *)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(227): note: “Cast”:“To”的 模板 参数无效，应为类型
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(230): error C2065: “UserStructType”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(230): error C2065: “UserStructType”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(231): error C2065: “UserStructType”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(251): warning C4996: 'UK2Node_CallFunction::bIsPureFunc': bIsPureFunc is deprecated. Use bDefaultsToPureFunc or IsNodePure instead. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
1>
1>Error executing C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.38.33130\bin\Hostx64\x64\cl.exe (tool returned code: 2)
1>[134/174] Compile [x64] WebInterfaceAssetManager.cpp (0:03.85 at +2:36)
1>[140/174] Compile [x64] SWebInterface.cpp (0:06.90 at +2:36)
1>C:\Users\chru\Desktop\VRGK55\Plugins\WebUI\Source\WebUI\Private\WebInterfaceAssetManager.cpp(10): warning C4996: 'TSoftObjectPtr<UMaterial>::TSoftObjectPtr': Constructing TSoftObjectPtr from an FString has been deprecated - instead, explicitly construct a FSoftObjectPath. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
1>C:\Users\chru\Desktop\VRGK55\Plugins\WebUI\Source\WebUI\Private\WebInterfaceAssetManager.cpp(11): warning C4996: 'TSoftObjectPtr<UMaterial>::TSoftObjectPtr': Constructing TSoftObjectPtr from an FString has been deprecated - instead, explicitly construct a FSoftObjectPath. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
1>C:\Users\chru\Desktop\VRGK55\Plugins\WebUI\Source\WebUI\Private\SWebInterface.cpp(424): warning C4996: 'FTexture2DRHIRef': The separate RHI texture types were unified in UE 5.1. FTexture2DRHIRef is now deprecated. Use FTextureRHIRef instead. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
1>[141/174] Compile [x64] WebInterfaceHelpers.cpp (0:05.56 at +2:37)
1>C:\Users\chru\Desktop\VRGK55\Plugins\WebUI\Source\WebUI\Private\SWebInterface.cpp(425): warning C4996: 'FTexture2DRHIRef': The separate RHI texture types were unified in UE 5.1. FTexture2DRHIRef is now deprecated. Use FTextureRHIRef instead. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
1>[142/174] Compile [x64] WebInterfaceSchemeHandler.cpp (0:03.82 at +2:40)
1>[145/174] Compile [x64] WebInterfaceInteractionComponent.cpp (0:06.84 at +2:38)
1>C:\Users\chru\Desktop\VRGK55\Plugins\WebUI\Source\WebUI\Private\SWebInterface.cpp(429): warning C4996: 'FTexture2DRHIRef': The separate RHI texture types were unified in UE 5.1. FTexture2DRHIRef is now deprecated. Use FTextureRHIRef instead. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
1>C:\Users\chru\Desktop\VRGK55\Plugins\WebUI\Source\WebUI\Private\WebInterfaceHelpers.cpp(150): warning C4996: 'TArray<TTuple<EImageFormat,IImageWrapper *>,FDefaultAllocator>::RemoveAtSwap': RemoveAtSwap with a boolean bAllowShrinking has been deprecated - please use the EAllowShrinking enum instead Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
1>[146/174] Compile [x64] WebInterface.cpp (0:08.92 at +2:36)
1>[157/174] Compile [x64] BlueprintAssistUtils.cpp (1:01.35 at +1:56)
1>C:\Users\chru\Desktop\VRGK55\Plugins\WebUI\Source\WebUI\Private\WebInterfaceInteractionComponent.cpp(139): warning C4701: 使用了可能未初始化的局部变量“WorldDirection”
1>   while compiling UWebInterfaceInteractionComponent::PerformTrace
1>---------------------- Done ----------------------
1>
1>    Rebuild All: 0 succeeded, 1 failed, 0 skipped
1>
1>1 build system warning(s):
1>   - License not activated
1>
1>Total time in XGE executor: 177.80 seconds
1>Total execution time: 180.82 seconds
1>C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Microsoft\VC\v170\Microsoft.MakeFile.Targets(44,5): error MSB3073: 命令“"C:\Program File\Epic Games\UE_5.5\Engine\Build\BatchFiles\Build.bat" VRGK2_427Editor Win64 DebugGame -Project="C:\Users\chru\Desktop\VRGK55\VRGK2_427.uproject" -WaitMutex -FromMsBuild -architecture=x64”已退出，代码为 6。
```

根据错误日志，主要问题集中在 JsonLibrary 和 WebUI 插件中。以下是针对 UE5.5 的兼容性修改步骤：

## 解决 UUserDefinedStruct 未声明错误

修改文件: Plugins/JsonLibrary/Source/JsonLibrary/Private/JsonLibraryConverter.cpp

添加头文件引用：
```
// 在文件头部添加
#include "Engine/UserDefinedStruct.h"
```
修正 IsA 和 StaticClass 调用：
```
// 原代码（约269行）:
if (Struct->IsA(UUserDefinedStruct::StaticClass()) 

// 修改为：
if (Struct->IsA(UUserDefinedStruct::StaticClass()))
```

## 修复 FProperty::ElementSize 弃用警告

修改文件: JsonLibraryConverter.cpp
```
// 原代码（约250行和946行）:
int32 ElementSize = Property->ElementSize; 

// 替换为：
int32 ElementSize = Property->GetElementSize();
```

## 处理 K2Node 中的 UUserDefinedStruct 错误
修改文件: Plugins/JsonLibrary/Source/JsonLibraryBlueprintSupport/Private/K2Node_JsonLibraryToStruct.cpp 和 K2Node_JsonLibraryFromStruct.cpp

添加头文件：
```
#include "Engine/UserDefinedStruct.h"
```

## 修复 bIsPureFunc 弃用警告

修改文件: K2Node_JsonLibraryFromStruct.cpp
```
// 原代码（约251行）:
bIsPureFunc = true;

// 替换为：
bIsCallFunctionPure = true; // 或使用 SetPurity(true);
```

## 处理 WebUI 插件警告

修改文件: SWebInterface.cpp
```
// 替换所有 FTexture2DRHIRef 为 FTextureRHIRef:
// 原代码:
FTexture2DRHIRef Texture;

// 修改为:
FTextureRHIRef Texture;
```

WebInterfaceHelpers.cpp 150行
```
// 修正 RemoveAtSwap 警告:
ImageWrappers.RemoveAtSwap(0);

// 修改为:
ImageWrappers.RemoveAtSwap(0, EAllowShrinking::No);
```

## 处理未初始化变量警告

修改文件: WebInterfaceInteractionComponent.cpp
```
// 原代码（约139行）:
FVector WorldDirection;

// 初始化变量:
FVector WorldDirection = FVector::ZeroVector;
```

## 更新插件描述文件（*.uplugin）
确保插件的 EngineVersion 兼容 UE5.5：

```
{
    "EngineVersion": "5.5",
    "Plugins": [...]
}
```
完成上述修改后，清理项目中间文件（Intermediate/ 和 Saved/ 目录），重新生成解决方案并编译。如果仍有其他错误，请检查 UE5.5 的 API 变更文档，调整对应的弃用方法。

# 第二轮报错

```cpp
1>[1/12] Compile [x64] JsonLibraryConverter.cpp
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(270): error C2653: “UUserDefinedStruct”: 不是类或命名空间名称
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(270): error C2672: “StaticClass”: 未找到匹配的重载函数
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\ReflectedTypeAccessors.h(13): note: 可能是“UClass *StaticClass(void)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(270): note: “UClass *StaticClass(void)”: 无法推导“ClassType”的 模板 参数
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(270): error C2672: “UObjectBaseUtility::IsA”: 未找到匹配的重载函数
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\UObjectBaseUtility.h(623): note: 可能是“bool UObjectBaseUtility::IsA(void) const”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(270): note: “bool UObjectBaseUtility::IsA(void) const”: 应输入 0 个参数，却提供了 1 个
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\UObjectBaseUtility.h(602): note: 或    “bool UObjectBaseUtility::IsA(OtherClassType) const”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(973): error C2653: “UUserDefinedStruct”: 不是类或命名空间名称
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(973): error C2672: “StaticClass”: 未找到匹配的重载函数
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\ReflectedTypeAccessors.h(13): note: 可能是“UClass *StaticClass(void)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(973): note: “UClass *StaticClass(void)”: 无法推导“ClassType”的 模板 参数
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(973): error C2672: “UObjectBaseUtility::IsA”: 未找到匹配的重载函数
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\UObjectBaseUtility.h(623): note: 可能是“bool UObjectBaseUtility::IsA(void) const”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(973): note: “bool UObjectBaseUtility::IsA(void) const”: 应输入 0 个参数，却提供了 1 个
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\UObjectBaseUtility.h(602): note: 或    “bool UObjectBaseUtility::IsA(OtherClassType) const”
1>[2/12] Compile [x64] WebInterfaceHelpers.cpp
1>C:\Users\chru\Desktop\VRGK55\Plugins\WebUI\Source\WebUI\Private\WebInterfaceHelpers.cpp(151): warning C4996: 'TArray<TTuple<EImageFormat,IImageWrapper *>,FDefaultAllocator>::RemoveAtSwap': RemoveAtSwap with a boolean bAllowShrinking has been deprecated - please use the EAllowShrinking enum instead Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\Core\Public\Containers\Array.h(1923): error C2660: “TArray<TTuple<EImageFormat,IImageWrapper *>,FDefaultAllocator>::RemoveAtSwap”: 函数不接受 3 个参数
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\Core\Public\Containers\Array.h(1880): note: 参见“TArray<TTuple<EImageFormat,IImageWrapper *>,FDefaultAllocator>::RemoveAtSwap”的声明
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\Core\Public\Containers\Array.h(1921): note: 可能是“void TArray<TTuple<EImageFormat,IImageWrapper *>,FDefaultAllocator>::RemoveAtSwap(int,CountType,bool)”
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\Core\Public\Containers\Array.h(1923): note: “初始化”: 无法从“EAllowShrinking”转换为“bool”
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\Core\Public\Containers\Array.h(1923): note: 此转换需要显式强制转换(static_cast、C 样式强制转换或带圆括号函数样式强制转换)
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\Core\Public\Containers\Array.h(1906): note: 或    “void TArray<TTuple<EImageFormat,IImageWrapper *>,FDefaultAllocator>::RemoveAtSwap(int,CountType,EAllowShrinking)”
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\Core\Public\Containers\Array.h(1923): note: 未满足关联约束
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\Core\Public\Containers\Array.h(1904): note: 未满足约束
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\Core\Public\Containers\Array.h(1923): note: 尝试匹配参数列表“(int, CountType, EAllowShrinking)”时
1>        with
1>        [
1>            CountType=EAllowShrinking
1>        ]
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\Core\Public\Containers\Array.h(1923): note: 模板实例化上下文(最早的实例化上下文)为
1>C:\Users\chru\Desktop\VRGK55\Plugins\WebUI\Source\WebUI\Private\WebInterfaceHelpers.cpp(151): note: 查看对正在编译的函数 模板 实例化“void TArray<TTuple<EImageFormat,IImageWrapper *>,FDefaultAllocator>::RemoveAtSwap<EAllowShrinking>(int,CountType,bool)”的引用
1>        with
1>        [
1>            CountType=EAllowShrinking
1>        ]
1>C:\Users\chru\Desktop\VRGK55\Plugins\WebUI\Source\WebUI\Private\WebInterfaceHelpers.cpp(151): note: 请参阅 "FGlobalInterfaceImageWrappers::FindOrCreateImageWrapper" 中对 "TArray<TTuple<EImageFormat,IImageWrapper *>,FDefaultAllocator>::RemoveAtSwap" 的第一个引用
1>[3/12] Compile [x64] K2Node_JsonLibraryToStruct.cpp
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(228): error C2065: “UUserDefinedStruct”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(228): error C2065: “UserStructType”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(228): error C2065: “UUserDefinedStruct”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(228): error C2672: “Cast”: 未找到匹配的重载函数
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\Linker.h(614): note: 可能是“T *Cast(FLinker *)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(228): note: “Cast”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h(411): note: 或    “const T *Cast(const U *)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(228): note: “Cast”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h(407): note: 或    “T *Cast(const TSubclassOf<U> &)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(228): note: “Cast”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h(295): note: 或    “TCopyQualifiersFromTo<From,To>::Type *Cast(const TObjectPtr<ValueType> &)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(228): note: “Cast”:“To”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h(289): note: 或    “T *Cast(const TWeakObjectPtr<UserClass,FWeakObjectPtr> &)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(228): note: “Cast”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\Core\Public\Delegates\DelegateSignatureImpl.inl(33): note: 或    “To *Cast(From *)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(228): note: “Cast”:“To”的 模板 参数无效，应为类型
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(231): error C2065: “UserStructType”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(231): error C2065: “UserStructType”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(232): error C2065: “UserStructType”: 未声明的标识符
1>[4/12] Compile [x64] K2Node_JsonLibraryFromStruct.cpp
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(227): error C2065: “UUserDefinedStruct”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(227): error C2065: “UserStructType”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(227): error C2065: “UUserDefinedStruct”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(227): error C2672: “Cast”: 未找到匹配的重载函数
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\Linker.h(614): note: 可能是“T *Cast(FLinker *)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(227): note: “Cast”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h(411): note: 或    “const T *Cast(const U *)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(227): note: “Cast”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h(407): note: 或    “T *Cast(const TSubclassOf<U> &)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(227): note: “Cast”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h(295): note: 或    “TCopyQualifiersFromTo<From,To>::Type *Cast(const TObjectPtr<ValueType> &)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(227): note: “Cast”:“To”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h(289): note: 或    “T *Cast(const TWeakObjectPtr<UserClass,FWeakObjectPtr> &)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(227): note: “Cast”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\Core\Public\Delegates\DelegateSignatureImpl.inl(33): note: 或    “To *Cast(From *)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(227): note: “Cast”:“To”的 模板 参数无效，应为类型
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(230): error C2065: “UserStructType”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(230): error C2065: “UserStructType”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(231): error C2065: “UserStructType”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(251): warning C4996: 'UK2Node_CallFunction::bIsPureFunc': bIsPureFunc is deprecated. Use bDefaultsToPureFunc or IsNodePure instead. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
1>C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Microsoft\VC\v170\Microsoft.MakeFile.Targets(44,5): error MSB3073: 命令“"C:\Program File\Epic Games\UE_5.5\Engine\Build\BatchFiles\Build.bat" VRGK2_427Editor Win64 DebugGame -Project="C:\Users\chru\Desktop\VRGK55\VRGK2_427.uproject" -WaitMutex -FromMsBuild -architecture=x64”已退出，代码为 6。
```

## 修复 FProperty::ElementSize 弃用警告

修改文件: JsonLibraryConverter.cpp
```
// 原代码（约250行和946行）:
int32 ElementSize = Property->ElementSize; 

// 替换为：
int32 ElementSize = Property->GetElementSize();
```

## 修正 StaticClass 调用语法

修改文件: JsonLibraryConverter.cpp
```
// 原代码（约270行和973行）:
if (Struct->IsA(UUserDefinedStruct::StaticClass()))

// 修改为：
if (Struct->IsA<UUserDefinedStruct>())  // 使用模板语法替代直接调用 StaticClass()
```

## 修复 RemoveAtSwap 参数类型错误

修改文件: Plugins/WebUI/Source/WebUI/Private/WebInterfaceHelpers.cpp
```
// 原代码（约151行）:
ImageWrappers.RemoveAtSwap(0, EAllowShrinking::No); 

// 根据 UE5.5 API 调整参数顺序：
ImageWrappers.RemoveAtSwap(0, 1, EAllowShrinking::No); 
// 或（如果只是删除单个元素）：
ImageWrappers.RemoveAtSwap(0, EAllowShrinking::No);  // 确认参数是否允许省略数量
```

## 处理 WebUI 插件警告

修改文件: SWebInterface.cpp
```
// 替换所有 FTexture2DRHIRef 为 FTextureRHIRef:
// 原代码:
FTexture2DRHIRef Texture;

// 修改为:
FTextureRHIRef Texture;
```
修正 RemoveAtSwap 警告:
```
// 原代码（WebInterfaceHelpers.cpp 150行）:
ImageWrappers.RemoveAtSwap(0);

// 修改为:
ImageWrappers.RemoveAtSwap(0, EAllowShrinking::No);
```

## 处理未初始化变量警告

修改文件: WebInterfaceInteractionComponent.cpp
```
// 原代码（约139行）:
FVector WorldDirection;

// 初始化变量:
FVector WorldDirection = FVector::ZeroVector;
```

## 验证头文件包含顺序修改文件:

```
Plugins/JsonLibrary/Source/JsonLibrary/Private/JsonLibraryConverter.cpp
Plugins/JsonLibrary/Source/JsonLibraryBlueprintSupport/Private/K2Node_JsonLibraryToStruct.cpp
Plugins/JsonLibrary/Source/JsonLibraryBlueprintSupport/Private/K2Node_JsonLibraryFromStruct.cpp
```
确保在引用 UUserDefinedStruct 的代码之前，已包含以下核心头文件：
```
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Engine/UserDefinedStruct.h"
```

## 修复 bIsPureFunc 弃用问题
修改文件: K2Node_JsonLibraryFromStruct.cpp（或相关文件）
```
// 原代码：
CallIsValidObjectFunction->bIsPureFunc = true;

// 修改为以下两种方式之一：

// --- 方法 1：通过函数标志直接声明为纯函数 ---
CallIsValidObjectFunction->FunctionFlags |= FUNC_BlueprintPure;  // 添加纯函数标志

// --- 方法 2：使用 UE5.5 推荐的节点设置接口 ---
CallIsValidObjectFunction->SetPurity(true);  // 直接设置节点为纯函数
```
完整代码显示
```
UK2Node_CallFunction* CallIsValidObjectFunction = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
CallIsValidObjectFunction->FunctionReference.SetExternalMember(IsValidObjectFunctionName, UJsonLibraryBlueprintHelpers::StaticClass());

// 选择以下任意一种方式：
CallIsValidObjectFunction->FunctionFlags |= FUNC_BlueprintPure;  // 方法1
// 或
CallIsValidObjectFunction->SetPurity(true);  // 方法2
```

# 第三轮报错

```cpp
1>[1/10] Compile [x64] JsonLibraryConverter.cpp
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(273): error C2065: “UUserDefinedStruct”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(273): error C2672: “UObjectBaseUtility::IsA”: 未找到匹配的重载函数
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\UObjectBaseUtility.h(623): note: 可能是“bool UObjectBaseUtility::IsA(void) const”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(273): note: “UObjectBaseUtility::IsA”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\UObjectBaseUtility.h(602): note: 或    “bool UObjectBaseUtility::IsA(OtherClassType) const”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(273): note: “UObjectBaseUtility::IsA”:“OtherClassType”的 模板 参数无效，应为类型
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(976): error C2065: “UUserDefinedStruct”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(976): error C2672: “UObjectBaseUtility::IsA”: 未找到匹配的重载函数
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\UObjectBaseUtility.h(623): note: 可能是“bool UObjectBaseUtility::IsA(void) const”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(976): note: “UObjectBaseUtility::IsA”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\UObjectBaseUtility.h(602): note: 或    “bool UObjectBaseUtility::IsA(OtherClassType) const”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(976): note: “UObjectBaseUtility::IsA”:“OtherClassType”的 模板 参数无效，应为类型
1>[2/10] Compile [x64] K2Node_JsonLibraryFromStruct.cpp
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(231): error C2065: “UUserDefinedStruct”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(231): error C2065: “UserStructType”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(231): error C2065: “UUserDefinedStruct”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(231): error C2672: “Cast”: 未找到匹配的重载函数
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\Linker.h(614): note: 可能是“T *Cast(FLinker *)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(231): note: “Cast”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h(411): note: 或    “const T *Cast(const U *)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(231): note: “Cast”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h(407): note: 或    “T *Cast(const TSubclassOf<U> &)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(231): note: “Cast”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h(295): note: 或    “TCopyQualifiersFromTo<From,To>::Type *Cast(const TObjectPtr<ValueType> &)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(231): note: “Cast”:“To”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h(289): note: 或    “T *Cast(const TWeakObjectPtr<UserClass,FWeakObjectPtr> &)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(231): note: “Cast”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\Core\Public\Delegates\DelegateSignatureImpl.inl(33): note: 或    “To *Cast(From *)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(231): note: “Cast”:“To”的 模板 参数无效，应为类型
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(234): error C2065: “UserStructType”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(234): error C2065: “UserStructType”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(235): error C2065: “UserStructType”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(255): error C2039: "SetPurity": 不是 "UK2Node_CallFunction" 的成员
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Editor\UnrealEd\Public\Kismet2\BlueprintEditorUtils.h(37): note: 参见“UK2Node_CallFunction”的声明
1>[3/10] Compile [x64] K2Node_JsonLibraryToStruct.cpp
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(231): error C2065: “UUserDefinedStruct”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(231): error C2065: “UserStructType”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(231): error C2065: “UUserDefinedStruct”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(231): error C2672: “Cast”: 未找到匹配的重载函数
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\Linker.h(614): note: 可能是“T *Cast(FLinker *)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(231): note: “Cast”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h(411): note: 或    “const T *Cast(const U *)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(231): note: “Cast”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h(407): note: 或    “T *Cast(const TSubclassOf<U> &)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(231): note: “Cast”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h(295): note: 或    “TCopyQualifiersFromTo<From,To>::Type *Cast(const TObjectPtr<ValueType> &)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(231): note: “Cast”:“To”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h(289): note: 或    “T *Cast(const TWeakObjectPtr<UserClass,FWeakObjectPtr> &)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(231): note: “Cast”:“T”的 模板 参数无效，应为类型
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\Core\Public\Delegates\DelegateSignatureImpl.inl(33): note: 或    “To *Cast(From *)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(231): note: “Cast”:“To”的 模板 参数无效，应为类型
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(234): error C2065: “UserStructType”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(234): error C2065: “UserStructType”: 未声明的标识符
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryToStruct.cpp(235): error C2065: “UserStructType”: 未声明的标识符
1>C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Microsoft\VC\v170\Microsoft.MakeFile.Targets(44,5): error MSB3073: 命令“"C:\Program File\Epic Games\UE_5.5\Engine\Build\BatchFiles\Build.bat" VRGK2_427Editor Win64 DebugGame -Project="C:\Users\chru\Desktop\VRGK55\VRGK2_427.uproject" -WaitMutex -FromMsBuild -architecture=x64”已退出，代码为 6。
```

## 彻底解决 UUserDefinedStruct 未声明问题

修改文件：
Plugins/JsonLibrary/Source/JsonLibrary/Private/JsonLibraryConverter.cpp
Plugins/JsonLibrary/Source/JsonLibraryBlueprintSupport/Private/K2Node_JsonLibraryToStruct.cpp
Plugins/JsonLibrary/Source/JsonLibraryBlueprintSupport/Private/K2Node_JsonLibraryFromStruct.cpp
在文件头部添加头文件引用：
```
#include "Engine/UserDefinedStruct.h"  // 必须包含此头文件
#include "UObject/Class.h"            // 确保基础类型定义存在
```
验证包含顺序：
确保 #include "Engine/UserDefinedStruct.h" 出现在所有引用 UUserDefinedStruct 的代码之前。

## 修复 IsA<UUserDefinedStruct>() 调用错误

修改文件: JsonLibraryConverter.cpp
```
// 原错误代码（约273行和976行）：
if (Struct->IsA<UUserDefinedStruct>()) 

// 修改为显式静态类调用（兼容 UE5.5 模板推导）：
if (Struct->IsA(UUserDefinedStruct::StaticClass())) 
```
原因：
UE5.5 的模板推导在某些情况下可能失败，直接使用 StaticClass() 更可靠。

## 修复 Cast<UUserDefinedStruct> 失败问题

修改文件:
K2Node_JsonLibraryToStruct.cpp
K2Node_JsonLibraryFromStruct.cpp

```
// 原错误代码（约231行）：
UUserDefinedStruct* UserStructType = Cast<UUserDefinedStruct>(StructType);

// 修改为显式指定模板参数：
UUserDefinedStruct* UserStructType = Cast<UUserDefinedStruct>(StructType); // 确保头文件已包含
```
验证：
确保 StructType 是 UStruct* 类型，且 UUserDefinedStruct 已正确定义。

## 修复 SetPurity 方法不存在问题

修改文件: K2Node_JsonLibraryFromStruct.cpp
```
// 原错误代码：
CallIsValidObjectFunction->SetPurity(true); // 此方法在 UE5.5 中不存在

// 替换为直接设置函数标志：
CallIsValidObjectFunction->FunctionFlags |= FUNC_BlueprintPure; // 标记为纯函数
```
确保已包含：
#include "UObject/Class.h" // 包含 FUNC_BlueprintPure 的定义

# 第四轮报错

```cpp
1>[1/10] Compile [x64] JsonLibraryConverter.cpp
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(273): error C2653: “UUserDefinedStruct”: 不是类或命名空间名称
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(273): error C2672: “StaticClass”: 未找到匹配的重载函数
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\ReflectedTypeAccessors.h(13): note: 可能是“UClass *StaticClass(void)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(273): note: “UClass *StaticClass(void)”: 无法推导“ClassType”的 模板 参数
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(273): error C2672: “UObjectBaseUtility::IsA”: 未找到匹配的重载函数
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\UObjectBaseUtility.h(623): note: 可能是“bool UObjectBaseUtility::IsA(void) const”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(273): note: “bool UObjectBaseUtility::IsA(void) const”: 应输入 0 个参数，却提供了 1 个
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\UObjectBaseUtility.h(602): note: 或    “bool UObjectBaseUtility::IsA(OtherClassType) const”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(976): error C2653: “UUserDefinedStruct”: 不是类或命名空间名称
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(976): error C2672: “StaticClass”: 未找到匹配的重载函数
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\ReflectedTypeAccessors.h(13): note: 可能是“UClass *StaticClass(void)”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(976): note: “UClass *StaticClass(void)”: 无法推导“ClassType”的 模板 参数
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(976): error C2672: “UObjectBaseUtility::IsA”: 未找到匹配的重载函数
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\UObjectBaseUtility.h(623): note: 可能是“bool UObjectBaseUtility::IsA(void) const”
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibrary\Private\JsonLibraryConverter.cpp(976): note: “bool UObjectBaseUtility::IsA(void) const”: 应输入 0 个参数，却提供了 1 个
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Runtime\CoreUObject\Public\UObject\UObjectBaseUtility.h(602): note: 或    “bool UObjectBaseUtility::IsA(OtherClassType) const”
1>[2/10] Compile [x64] K2Node_JsonLibraryFromStruct.cpp
1>C:\Users\chru\Desktop\VRGK55\Plugins\JsonLibrary\Source\JsonLibraryBlueprintSupport\Private\K2Node_JsonLibraryFromStruct.cpp(257): error C2039: "FunctionFlags": 不是 "UK2Node_CallFunction" 的成员
1>C:\Program File\Epic Games\UE_5.5\Engine\Source\Editor\UnrealEd\Public\Kismet2\BlueprintEditorUtils.h(37): note: 参见“UK2Node_CallFunction”的声明
1>C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Microsoft\VC\v170\Microsoft.MakeFile.Targets(44,5): error MSB3073: 命令“"C:\Program File\Epic Games\UE_5.5\Engine\Build\BatchFiles\Build.bat" VRGK2_427Editor Win64 DebugGame -Project="C:\Users\chru\Desktop\VRGK55\VRGK2_427.uproject" -WaitMutex -FromMsBuild -architecture=x64”已退出，代码为 6。
```
</code></pre>
</details>