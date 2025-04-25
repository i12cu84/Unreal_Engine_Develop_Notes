[VRGK V3 Github社区版](https://github.com/santyvv1993/VRGK-Community-Project-UE5)

引擎UE5.3

更新内容:
提升引擎版本(Epic商城版UE4.27及以上,Github社区版5.3及以上)
在Metaquest 3中完美运行

---

[旧版文档 PDF](https://divivor.itch.io/legacy-docs) (访问密码：legacydocs)

[VRGK V3 Epic Game 商城版(已被废弃)](https://www.unrealengine.com/marketplace/en-US/product/vrgk-virtual-reality-game-kit)

[VRGK V3 文档](https://itchio-mirror.cb031a832f44726753d6267436f3b414.r2.cloudflarestorage.com/upload2/game/2174829/8374307?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=3edfcce40115d057d0b5606758e7e9ee%2F20250408%2Fauto%2Fs3%2Faws4_request&X-Amz-Date=20250408T060804Z&X-Amz-Expires=60&X-Amz-SignedHeaders=host&X-Amz-Signature=321ee1085fb326fa7fe5367fcdde0de9a1a695ee8be433ed4a47899a8c64564c)


---

1.尝试将项目升级到5.5

最终项目升级失败,原因是缺少SteamVR插件(5.3起已被废弃)
<details>
<summary>无效内容折叠</summary>
<pre><code>

SteamVR/OculusVR插件被废弃.需要将".uproject"以记事本打开,并**删除**以下内容
```
{
    "Name": "SteamVR",
    "Enabled": true,
    "SupportedTargetPlatforms": [
        "Win64",
        "Linux"
    ]
},
{
    "Name": "OculusVR",
    "Enabled": true,
    "SupportedTargetPlatforms": [
        "Win64",
        "Android"
    ]
},
```

构建cpp Source文件.以"VRGK2_427"项目为例

VRGK2_427.Target.cs
```
using UnrealBuildTool;
using System.Collections.Generic;

public class VRGK2_427Target : TargetRules
{
	public VRGK2_427Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
        CppStandard = CppStandardVersion.Cpp20;

        // 显式声明严格模式（必须与引擎默认值True一致）
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            WindowsPlatform.bStrictConformanceMode = true; // 关键修复点
        }

        /*

        // 禁用所有可能覆盖引擎默认值的设置
        bLegacyParentIncludePaths = false;
        bValidateFormatStrings = true;

        */

        ExtraModuleNames.AddRange( new string[] { "VRGK2_427" } );
	}
}
```
VRGK2_427Editor.Target.cs
```
using UnrealBuildTool;
using System.Collections.Generic;

public class VRGK2_427EditorTarget : TargetRules
{
	public VRGK2_427EditorTarget(TargetInfo Target) : base(Target)
	{
        Type = TargetType.Editor; // 编辑器专用配置
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
        CppStandard = CppStandardVersion.Cpp20;

        // 与游戏目标保持一致的严格模式
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            WindowsPlatform.bStrictConformanceMode = true;
        }

        ExtraModuleNames.AddRange( new string[] { "VRGK2_427" } );
	}
}
```
VRGK2_427/VRGK2_427.Build.cs //VRGK2_427是项目名字
```
using UnrealBuildTool;

public class VRGK2_427 : ModuleRules
{
	public VRGK2_427(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		// 旧代码
        //bEnableUndefinedIdentifierWarnings = false;

        // 新代码
        UndefinedIdentifierWarningLevel = WarningLevel.Off;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore"});

		PrivateDependencyModuleNames.AddRange(new string[] {});

        // 替换过时的警告设置
        UndefinedIdentifierWarningLevel = WarningLevel.Off; // 替代旧版bEnableUndefinedIdentifierWarnings

        // 其他模块依赖配置保持不变
        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore"
        });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
```

将如上三个文件放到Source

右键.uproject文件 -> Generate Visual Studio project files (生成Visual Studio项目文件)

VS打开开始编译
</code></pre>
</details>