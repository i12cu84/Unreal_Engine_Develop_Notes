在项目根目录创建Source文件夹

右键.uproject文件 -> Generate Visual Studio project files (生成Visual Studio项目文件) ->

在Source文件夹中新建 三个文件

(文件1)项目名##.Target.cs文件,例如LPSP.Target.cs
---
```cpp
using UnrealBuildTool;
using System.Collections.Generic;

public class 项目名Target : TargetRules
{
	public 项目名Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "项目名" } );
	}
}
```

(文件2)项目名##Editor.Target.cs的文件,例如LPSPEditor.Target.cs
---
```cpp
using UnrealBuildTool;
using System.Collections.Generic;

public class 项目名EditorTarget : TargetRules
{
	public 项目名EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "项目名" } );
	}
}
```

(文件3,包含文件夹)一个项目名文件夹，文件夹中新建 项目名##Build.cs文件,例如LPSP/LPSP.Build.cs
---
```cpp
using UnrealBuildTool;

public class 项目名 : ModuleRules
{
	public 项目名(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		bEnableUndefinedIdentifierWarnings = false; //出现冲突的时候可以尝试加这一句
		
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore"});

		PrivateDependencyModuleNames.AddRange(new string[] {});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
```

然后重新编译生成项目,即可

注意,vs打开项目之后,在右侧的"解决方案资源管理器"中将"Game"的项目右键"设为启动项目"再尝试编译