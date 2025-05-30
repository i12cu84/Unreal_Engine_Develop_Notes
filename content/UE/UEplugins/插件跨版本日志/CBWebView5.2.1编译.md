```

1>Using bundled DotNet SDK version: 6.0.302
1>Running UnrealBuildTool: dotnet "..\..\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.dll" Task521Editor Win64 DebugGame -Project="C:\Users\chru\Desktop\Task521\Task521.uproject" -WaitMutex -FromMsBuild
1>Log file: C:\Users\chru\AppData\Local\UnrealBuildTool\Log.txt
1>Invalidating makefile for Task521Editor (CBWebView2.uplugin has been added)
1>Building Task521Editor...
1>Using Visual Studio 2022 14.34.31948 toolchain (C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.34.31933) and Windows 10.0.18362.0 SDK (C:\Program Files (x86)\Windows Kits\10).
1>[Upgrade]
1>[Upgrade] Using backward-compatible include order. The latest version of UE has changed the order of includes, which may require code changes. The current setting is:
1>[Upgrade]     IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1
1>[Upgrade] Suppress this message by setting 'IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_2;' in Task521Editor.Target.cs.
1>[Upgrade] Alternatively you can set this to 'EngineIncludeOrderVersion.Latest' to always use the latest include order. This will potentially cause compile errors when integrating new versions of the engine.
1>[Upgrade]
1>Determining max actions to execute in parallel (16 physical cores, 24 logical cores)
1>  Executing up to 16 processes, one per physical core
1>Distributing 24 actions to XGE
1>UnrealBuildTool Compile
1>
1>--------------------Build System Warning---------------------------------------
1>License not activated:
1>    License is not activated. Please activate the license in the coordinator.
1>    This build will run in standalone mode.
1>
1>-------------------------------------------------------------------------------
1>
1>Build ID: {E2F26377-076E-44BA-AC5C-E39A7DCF2390}
1>
1>--------------------Project: Default-------------------------------------------
1>[1/24] Default.rc2 (0:00.09 at +0:00)
1>[2/24] Default.rc2 (0:00.09 at +0:00)
1>[3/24] SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.cpp (0:17.70 at +0:00)
1>[4/24] SharedPCH.Engine.NonOptimized.ShadowErrors.NoUndef.InclOrderUnreal5_1.cpp (0:18.09 at +0:00)
1>[5/24] WebView2Settings.gen.cpp (0:01.48 at +0:17)
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(75): warning C4005: “WINVER”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(54): note: 参见“WINVER”的前一个定义
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(76): warning C4005: “_WIN32_WINNT”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(53): note: 参见“_WIN32_WINNT”的前一个定义
1>[6/24] WebView2Settings.cpp (0:01.45 at +0:17)
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(75): warning C4005: “WINVER”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(54): note: 参见“WINVER”的前一个定义
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(76): warning C4005: “_WIN32_WINNT”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(53): note: 参见“_WIN32_WINNT”的前一个定义
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Source\WebView2Utils\Private\WebView2Settings.cpp(7): warning C5038: 数据成员“UWebView2Settings::bMuted”将在 数据成员“UWebView2Settings::WebView2Mode”后初始化
1>[7/24] WebView2Types.cpp (0:01.50 at +0:17)
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(75): warning C4005: “WINVER”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(54): note: 参见“WINVER”的前一个定义
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(76): warning C4005: “_WIN32_WINNT”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(53): note: 参见“_WIN32_WINNT”的前一个定义
1>[8/24] WebView2Utils.init.gen.cpp (0:01.56 at +0:17)
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(75): warning C4005: “WINVER”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(54): note: 参见“WINVER”的前一个定义
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(76): warning C4005: “_WIN32_WINNT”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(53): note: 参见“_WIN32_WINNT”的前一个定义
1>[9/24] WebView2Utils.cpp (0:01.53 at +0:17)
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(75): warning C4005: “WINVER”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(54): note: 参见“WINVER”的前一个定义
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(76): warning C4005: “_WIN32_WINNT”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(53): note: 参见“_WIN32_WINNT”的前一个定义
1>[10/24] WebView2Subsystem.gen.cpp (0:01.54 at +0:17)
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(75): warning C4005: “WINVER”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(54): note: 参见“WINVER”的前一个定义
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(76): warning C4005: “_WIN32_WINNT”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(53): note: 参见“_WIN32_WINNT”的前一个定义
1>[11/24] WebView2ComponentBase.cpp (0:02.04 at +0:17)
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(75): warning C4005: “WINVER”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(54): note: 参见“WINVER”的前一个定义
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(76): warning C4005: “_WIN32_WINNT”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(53): note: 参见“_WIN32_WINNT”的前一个定义
1>[12/24] WebView2FileComponent.cpp (0:02.06 at +0:17)
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(75): warning C4005: “WINVER”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(54): note: 参见“WINVER”的前一个定义
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(76): warning C4005: “_WIN32_WINNT”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(53): note: 参见“_WIN32_WINNT”的前一个定义
1>[13/24] WebView2Manager.cpp (0:02.70 at +0:17)
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(75): warning C4005: “WINVER”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(54): note: 参见“WINVER”的前一个定义
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(76): warning C4005: “_WIN32_WINNT”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(53): note: 参见“_WIN32_WINNT”的前一个定义
1>C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.34.31933\INCLUDE\experimental\coroutine(36): fatal error C1189: #error:  The <experimental/coroutine> and <experimental/resumable> headers are only supported with /await and implement pre-C++20 coroutine support. Use <coroutine> for standard C++20 coroutines.
1>
1>Error executing C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.34.31933\bin\Hostx64\x64\cl.exe (tool returned code: 2)
1>[14/24] WebView2CompositionHost.cpp (0:02.71 at +0:17)
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(75): warning C4005: “WINVER”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(54): note: 参见“WINVER”的前一个定义
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(76): warning C4005: “_WIN32_WINNT”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(53): note: 参见“_WIN32_WINNT”的前一个定义
1>C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.34.31933\INCLUDE\experimental\coroutine(36): fatal error C1189: #error:  The <experimental/coroutine> and <experimental/resumable> headers are only supported with /await and implement pre-C++20 coroutine support. Use <coroutine> for standard C++20 coroutines.
1>
1>Error executing C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.34.31933\bin\Hostx64\x64\cl.exe (tool returned code: 2)
1>[15/24] WebView2Subsystem.cpp (0:02.75 at +0:17)
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(75): warning C4005: “WINVER”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(54): note: 参见“WINVER”的前一个定义
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(76): warning C4005: “_WIN32_WINNT”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(53): note: 参见“_WIN32_WINNT”的前一个定义
1>C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.34.31933\INCLUDE\experimental\coroutine(36): fatal error C1189: #error:  The <experimental/coroutine> and <experimental/resumable> headers are only supported with /await and implement pre-C++20 coroutine support. Use <coroutine> for standard C++20 coroutines.
1>
1>Error executing C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.34.31933\bin\Hostx64\x64\cl.exe (tool returned code: 2)
1>[16/24] WebView2Window.gen.cpp (0:02.71 at +0:17)
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(75): warning C4005: “WINVER”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(54): note: 参见“WINVER”的前一个定义
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(76): warning C4005: “_WIN32_WINNT”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(53): note: 参见“_WIN32_WINNT”的前一个定义
1>C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.34.31933\INCLUDE\experimental\coroutine(36): fatal error C1189: #error:  The <experimental/coroutine> and <experimental/resumable> headers are only supported with /await and implement pre-C++20 coroutine support. Use <coroutine> for standard C++20 coroutines.
1>
1>Error executing C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.34.31933\bin\Hostx64\x64\cl.exe (tool returned code: 2)
1>[17/24] WebView2Window.cpp (0:02.71 at +0:17)
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(75): warning C4005: “WINVER”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(54): note: 参见“WINVER”的前一个定义
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(76): warning C4005: “_WIN32_WINNT”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(53): note: 参见“_WIN32_WINNT”的前一个定义
1>C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.34.31933\INCLUDE\experimental\coroutine(36): fatal error C1189: #error:  The <experimental/coroutine> and <experimental/resumable> headers are only supported with /await and implement pre-C++20 coroutine support. Use <coroutine> for standard C++20 coroutines.
1>
1>Error executing C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.34.31933\bin\Hostx64\x64\cl.exe (tool returned code: 2)
1>[18/24] WebView2ViewComponent.cpp (0:02.73 at +0:17)
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(75): warning C4005: “WINVER”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(54): note: 参见“WINVER”的前一个定义
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\WebView2Utils\Definitions.WebView2Utils.h(76): warning C4005: “_WIN32_WINNT”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\UnrealEd\SharedPCH.UnrealEd.NonOptimized.ShadowErrors.Cpp20.InclOrderUnreal5_1.h(53): note: 参见“_WIN32_WINNT”的前一个定义
1>C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.34.31933\INCLUDE\experimental\coroutine(36): fatal error C1189: #error:  The <experimental/coroutine> and <experimental/resumable> headers are only supported with /await and implement pre-C++20 coroutine support. Use <coroutine> for standard C++20 coroutines.
1>
1>Error executing C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.34.31933\bin\Hostx64\x64\cl.exe (tool returned code: 2)
1>[19/24] Module.CBWebView2.cpp (0:08.90 at +0:18)
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\CBWebView2\Definitions.CBWebView2.h(391): warning C4005: “WINVER”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\Engine\SharedPCH.Engine.NonOptimized.ShadowErrors.NoUndef.InclOrderUnreal5_1.h(54): note: 参见“WINVER”的前一个定义
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Intermediate\Build\Win64\x64\UnrealEditor\DebugGame\CBWebView2\Definitions.CBWebView2.h(392): warning C4005: “_WIN32_WINNT”: 宏重定义
1>C:\Users\chru\Desktop\Task521\Intermediate\Build\Win64\x64\Task521Editor\DebugGame\Engine\SharedPCH.Engine.NonOptimized.ShadowErrors.NoUndef.InclOrderUnreal5_1.h(53): note: 参见“_WIN32_WINNT”的前一个定义
1>C:\Users\chru\Desktop\Task521\Plugins\CBWebView2\Source\CBWebView2\Public\SCBWebView2.h(15): warning C5038: 数据成员“SCBWebView2::FArguments::_ShowAddressBar”将在 数据成员“SCBWebView2::FArguments::_ShowTouchArea”后初始化
1>---------------------- Done ----------------------
1>
1>    Rebuild All: 0 succeeded, 1 failed, 0 skipped
1>
1>1 build system warning(s):
1>   - License not activated
1>
1>C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Microsoft\VC\v170\Microsoft.MakeFile.Targets(44,5): error MSB3073: 命令“"C:\Program Files\Epic Games\UE_5.2\Engine\Build\BatchFiles\Build.bat" Task521Editor Win64 DebugGame -Project="C:\Users\chru\Desktop\Task521\Task521.uproject" -WaitMutex -FromMsBuild”已退出，代码为 6。
1>已完成生成项目“Task521.vcxproj”的操作 - 失败。
========== 生成: 0 成功，1 失败，0 最新，0 已跳过 ==========
```