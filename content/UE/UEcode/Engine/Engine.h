// C:\Program Files\Epic Games\UE_5.2\Engine\Source\Runtime\Engine\Classes\Engine\World.h

// 动态解析状态的信息。
struct FDynamicResolutionStateInfos
{
};

// 结构体以帮助保存关于需要为DLC完全加载的包的信息，等等
struct FFullyLoadedPackagesInfo
{
};

// 在提交map更改后立即应用的级别流更新
struct FLevelStreamingStatus
{
};

/*
 *用于描述引擎可用的各种类型的网络驱动程序的容器
 *引擎将尝试构建给定类型的netdriver，如果失败，
 *备用版本。
 */
struct FNetDriverDefinition
{
};

/*
 *用于配置启动哪个NetDriver时是否启用Iris的Struct
 * NetDriverDefinition中只有一个属性，netdriverame或NetDriverWildcardName应该与bEnableIris属性一起设置
 */
struct FIrisNetDriverConfig
{
};

/*
 *从FNetDriverDefinition实例化的活动和命名的网络驱动程序
 *网络驱动程序将保持在这个结构体上实例化，直到它被销毁
 */
struct FNamedNetDriver
{
};

/*
 FWorldContext
*用于在引擎级别处理UWorlds的上下文。当引擎升起并摧毁世界时，我们需要一种保持直线的方法
*什么世界属于什么。
*
* worldcontexts可以被认为是一个轨迹。默认情况下，我们有一个轨道，我们加载和卸载水平。添加第二个上下文就是添加
*第二个音轨;这是世界生存的另一条发展道路。
*
*对于GameEngine来说，在我们决定支持多个同时存在的世界之前，将只有一个世界上下文。
*对于editoengine，可能有一个EditorWorld和一个PIE世界的WorldContext。
*
* fworldcontext提供了一种管理`当前PIE UWorld `的方法，以及与连接/传递相关的状态
*新的世界。
*
* fworldcontext应该保持在UEngine类的内部。外部代码不应该保留指针或试图直接管理FWorldContexts。
*外部代码仍然可以处理UWorld，并将UWorld传递给引擎级函数。引擎代码可以查找相关的上下文
*对于给定的UWorld*。
*
*为了方便起见，FWorldContext可以维护指向UWorld*s的外部指针。例如，PIE可以将UWorld* ueditoengine::PlayWorld绑定到PIE
*世界上下文。如果饼图UWorld发生变化，ueditoengine::PlayWorld指针将自动更新。这是通过AddRef()和完成的
* SetCurrentWorld()。
*
*/
struct FWorldContext
{
};

//
struct FStatColorMapEntry
{
};

//
struct FStatColorMapping
{
};

// 关于在PIE过程中放入到map中的一个音符的信息。
struct FDropNoteInfo
{
};

// 屏幕上调试消息处理
// 用于跟踪屏幕消息的辅助结构体。
struct FScreenMessageString
{
};

//
struct FGameNameRedirect
{
};

//
struct FClassRedirect
{
};

//
struct FStructRedirect
{
};

//
struct FPluginRedirect
{
};

/*
 *所有引擎类的抽象基类，负责管理对编辑器或游戏系统至关重要的系统。
 *还定义了某些引擎系统的默认类。
 */
class ENGINE_API UEngine
{
};

// 全局引擎指针。可以为0，所以请不要未经检查就使用。
extern ENGINE_API class UEngine *GEngine;