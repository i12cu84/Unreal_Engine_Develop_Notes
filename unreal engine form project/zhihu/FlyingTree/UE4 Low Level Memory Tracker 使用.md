
<details>
<summary>UE4 Low Level Memory Tracker 使用</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/78005333
LLM(Low Level Memory Tracker) 是从 4.18 开始引入的新的内存统计工具，比 memreport 统计数据更加详细精确，但又不会像 MallocProfiler 那样有很大的本身开销
相关代码实现在 Engine\Source\Runtime\Core\Public\HAL\LowLevelMemTracker.h 和 Engine\Source\Runtime\Core\Private\HAL\LowLevelMemTracker.cpp 中
本文基于 UE4.23 分析使用 LLM
编译开关
在 Development 和 Debug 下，LLM 相关的代码是默认编译的，在 Test 模式下，需要在 YourGame.Target.cs 文件中增加宏定义 ALLOW_LOW_LEVEL_MEM_TRACKER_IN_TEST=1 才会编译相关代码，Shipping 模式下不会编译
运行开关
在编译时打开 LLM 后，要想在运行时使用 LLM 的功能，还要加上启动命令行 -LLM -LLMCSV
-LLM：运行时打开 LLM 统计
-LLMCSV：将内存统计信息输出到 CSV 文件中，CSV 文件保存在 Saved\Profiling\LLM 目录下
如果想在运行时默认生效，可以在 Target.cs 文件中增加宏定义 LLM_AUTO_ENABLE=1
另外还有个命令行 -LLMTAGSETS，用来指示资源统计分类是按类别来分，还是按具体资源来分，不过要使用这个功能需要在编译时在代码中打开 LLM_ALLOW_ASSETS_TAGS 宏(这个宏目前不能在 Target.cs 文件添加)
-LLMTAGSETS=Assets：按资源分类统计
-LLMTAGSETS=AssetClasses：按资源类别分类统计
运行时开关 LLM 的处理见 FLowLevelMemTracker::ProcessCommandLine 函数
Android 命令行
在已经装好版本的手机上，如果想要启动 LLM，可以通过 push UE4CommandLine.txt 到手机上动态改变游戏启动参数
新建一个 UE4CommandLine.txt，内容如下
../../../YourProject/YourProject.uproject -LLM -LLMCSV
新建一个 PushCommandLine.bat 并执行，内容如下
%ANDROID_HOME%\platform-tools\adb.exe shell mkdir -p /sdcard/UE4Game/YourProject
%ANDROID_HOME%\platform-tools\adb.exe push UE4CommandLine.txt /sdcard/UE4Game/YourProject/UE4CommandLine.txt
IOS 命令行
IOS 需要将 ue4commandline.txt 通过文件共享复制到 Documents 目录下，注意这里的文件名是全小写
显示统计命令行
运行时，可以通过以下命令行来显示当前的统计信息
stat LLM: 显示 Default Tracker 分组的简要内存统计信息
stat LLMFULL: 显示 Default Tracker 分组的所有内存统计信息
stat LLMOveread: 显示 LLM 本身使用的内存信息
stat LLMPlatform: 显示 Platform Tracker 分组的内存统计信息
LLM.LLMWriteInterval: 修改 LLM 的内存信息写入 csv 文件的频率，默认 5 秒写一行
LLMASSETS 命令行
编译时打开 LLM_ALLOW_ASSETS_TAGS，运行时指定 -LLMTAGSETS=Assets，执行 stat LLMAssets 命令行效果如下:
运行时指定 -LLMTAGSETS=AssetClasses，执行 stat LLMAssets 命令行效果如下:
CSV 文件输出
指定 -LLMCSV 命令行后，会得到两个 csv 文件，一个是 LLM_ 前缀，另一个是 LLMPlatform_ 前缀，这两个文件分别由两个 Tracker 生成，这两个文件的关注点不同
LLMPlatform 只关注系统内存的消费者，主要有几大类: ProgramSize, FMalloc, LLMOverhead。
LLM 主要关注 FMalloc 内存的消费者，主要就是引擎内各个部分的内存开销
注意，当同时指定 -LLMTAGSETS 命令行后，CSV 文件会错乱，因为写 CSV 文件时预留了第一行标题栏内容的缓冲区，当打开 LLMTAGSETS 之后，因为每个资源或资源类很多，会导致标题栏内容溢出，覆盖了后面的数据区域，所以这里需要自己按需求修改一下
LLM 统计分类
Total: 总内存
ELLMTag::PlatformTotal: 在 Android 上为 RSS，在 iOS 上为 resident_size，在其它平台上为系统所有进程消耗的内存(不明白这里为什么是这样)，所以这个值目前只有在移动端有参考意义
ELLMTag::Total: PlatformTotal - LLM Overhead，即为上面的内存减去 LLM 本身消耗的内存，这个内存值可以认为是在不打开 LLM 功能下的进程内存值，同上，这个值目前只在移动端上有参考意义
ELLMTag::PlatformOverhead: 即 LLMOverhead，LLM 本身消耗的内存
TrackedTotal: 通过调用 LLM OnLowLevelAlloc/OnLowLevelFree 统计到的所有内存
ELLMTag::PlatformTrackedTotal: Tracker 类型为 ELLMTracker::Platform
ELLMTag::TrackedTotal: Tracker 类型为 ELLMTracker::Default
Untracked: 未知的内存分配，即 LLM 无法追踪的内存，比如第三方库里的内存分配
ELLMTag::PlatformUntracked: PlatformTotal - PlatformTrackedTotal
ELLMTag::Untracked: Total - TrackedTotal
ELLMTag::Untagged: 未分类的内存，即分配内存时候不在 LLM_SCOPE 宏范围内
ELLMTag::FMalloc: 通过 FMallocBinned/FMallocBinned2 内存分配器分配的内存，也就是一般意义上引擎分配的内存，比如各种UObject，纹理，动画等占用的内存
ELLMTag::FMallocUnused: 通过 FMemory 分配的内存与 ELLMTag::FMalloc 类别内存的差值
ProgramSize: 程序刚起来时占用的内存，即刚进 Main 函数时，在 Android 上为 RSS，在 iOS 上为 resident_size
ELLMTag::ProgramSize
ELLMTag::ProgramSizePlatform
OOMBackupPool: Out of memory 备用内存池
ELLMTag::BackupOOMMemoryPoolPlatform
ELLMTag::BackupOOMMemoryPool
GenericPlatformMallocCrash: 预分配的 crash 相关的内存，当 crash 发生时用来替换 GMalloc
ELLMTag::GenericPlatformMallocCrashPlatform
ELLMTag::GenericPlatformMallocCrash
ELLMTag::EngineMisc: 在以下函数执行过程中分配的内存
AActor::ProcessEvent
UPackageMapClient::SerializeNewActor
FEngineLoop::Tick
ELLMTag::TaskGraphTasksMisc: FTaskThreadAnyThread::ProcessTasks 函数执行过程中分配的内存
Audio: 音频相关的内存，包括音频资源，音频线程中分配的内存，具体还包含以下子类别
ELLMTag::AudioMisc
ELLMTag::AudioSoundWaves
ELLMTag::AudioMixer
ELLMTag::AudioPrecache
ELLMTag::AudioDecompress
ELLMTag::AudioRealtimePrecache
ELLMTag::AudioFullDecompress
ELLMTag::AudioVoiceChat
ELLMTag::FName: FName 资源占用的内存
ELLMTag::Networking: 网络相关的内存，包含网络包处理，连接对象内存等
ELLMTag::Meshes: Mesh 的顶点缓存，顶点索引缓存占用的内存，还有以下子类别
ELLMTag::StaticMesh: StaticMesh 相关的内存，包含 StaticMesh 资源，StaticMeshComponent
ELLMTag::SkeletalMesh: SkeletalMeshComponent, SkinnedMeshComponent, SkeletalMesh 内存
ELLMTag::InstancedMesh: InstancedStaticMeshComponent, HierarchicalInstancedStaticMeshComponent 内存
ELLMTag::Landscape: LandscapeComponent, LandscapeProxy, LandscapeComponentSceneProxy 内存
ELLMTag::Stats: stat 统计相关的内存占用
ELLMTag::Shaders: 各种类型 Shander 的内存占用
ELLMTag::PSO: Pipeline State Object 缓存的内存占用
ELLMTag::Textures: 纹理相关的内存占用
ELLMTag::TextureMetaData: UTexture2D::Serialize 函数执行过程中分配的内存
ELLMTag::RenderTargets: RT 相关的内存，包含在 Viewport 中渲染使用的内存
ELLMTag::SceneRender: 场景渲染相关的内存占用，包含 Slate RHI Render 的窗口渲染
ELLMTag::RHIMisc: 其它渲染相关的内存占用，如各种渲染状态，RHI Thread 运行过程中的内存
ELLMTag::AsyncLoading: 异步资源加载过程中的内存占用，包含 AsyncLoadingThread, Event Driven Loader
ELLMTag::UObject: UObject 占用的内存，包含 UClass 等
ELLMTag::Animation: 动画相关的内存，包含 AnimInstance, AnimSequence, AnimationAsset, AnimBlueprint, MorphTarget
ELLMTag::Materials: 材质相关的内存，包含 MaterialInterface, MaterialFunction
ELLMTag::Particles: 特效相关的内存，包含 ParticleSystemComponent
ELLMTag::GC: GC 过程中的内存，分别为以下两个函数
CollectGarbageInternal
PerformReachabilityAnalysis
ELLMTag::UI: Slate 相关的内存，包含字体，TextureAtlas
ELLMTag::PhysX: PhysX 物理相关的内存
ELLMTag::EnginePreInitMemory: FEngineLoop::PreInit 函数执行过程中的内存
ELLMTag::EngineInitMemory: FEngineLoop::Init 函数执行过程中的内存
ELLMTag::RenderingThreadMemory: 渲染线程(RenderingThreadMain)执行过程中的内存
ELLMTag::LoadMapMisc: 地图加载过程中的内存，分别为以下两个函数
UEngine::LoadMap
UWorld::UpdateLevelStreaming
ELLMTag::StreamingManager: StreamableManager 相关的内存，主要是资源 streaming 函数执行过程中的内存
ELLMTag::GraphicsPlatform: 显存，只在 D3D，Vulkan 上有
ELLMTag::FileSystem: 文件系统相关的内存，主要是文件读取时的缓冲区，比如 Pak 文件
ELLMTag::Localization: 本地化相关的内存
ELLMTag::AssetRegistry: AssetRegistryModule 内存
ELLMTag::ConfigSystem: 配置文件相关的内存
ELLMTag::InitUObject: InitUObject 函数执行过程中的内存
ELLMTag::MaterialInstance: MaterialInstance, MaterialInstanceDynamic 包括材质参数内存占用
ELLMTag::Lua: Lua 内存
Windows 标签
ELLMTag::WorkingSetSize: 进程物理内存，可用这个值替代上面的 PlatformTotal
ELLMTag::PagefileUsed: 进程虚拟内存
ThreadStack: Windows 线程栈内存
ELLMTag::ThreadStackPlatform
ELLMTag::ThreadStack
添加自定义标签
除了以上的分类标签外，还可以添加自定义的标签，主要有两种方式
第一种是直接修改 LowLevelMemTrakcer.h 文件，在 LLM_ENUM_GENERIC_TAGS 宏内按同样格式添加一个新标签定义
另外一种是通过调用 RegisterPlatformTag/RegisterProjectTag 来动态地注册新标签，主要参数如下:
Tag: 标签枚举，不要和其它地方重复了
Name: 标签名，显示在 CSV 文件的标题栏中
StatName: 与这个标签相关的 Stat 统计，在游戏中通过 stat 命令来显示，使用 DECLARE_LLM_MEMORY_STAT 宏进行定义，可以为空(NAME_None)
SummaryStatName: 汇总 Stat 统计，可以将多个 LLM STAT 汇总在一起，可以为空(NAME_None)
ParentTag: 父级标签枚举值，父级标签对应的内存值是所有子级标签的和，级数最多两级
DECLARE_LLM_MEMORY_STAT(TEXT("Test"), STAT_TestLLM, STATGROUP_LLMFULL);
enum class EMyLLMTag
{
  TestTag = ELLMTag::ProjectTagStart + 20,
}
void Init()
{
  LLM(FLowLevelMemTracker::Get().RegisterProjectTag((int32)EMyLLMTag::TestTag, TEXT("Test"), GET_STATFNAME(STAT_TestLLM), NAME_None));
}
void TestFunc()
{
    LLM_SCOPE(EMyLLMTag::TestTag);
}
</code></pre>
</details>