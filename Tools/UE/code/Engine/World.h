// C:\Program Files\Epic Games\UE_5.2\Engine\Source\Runtime\Engine\Classes\Engine\World.h

// 允许对GWorld访问进行验证的代理类。
class UWorldProxy
{
};

// 注册到音频设备的代表列表
class ENGINE_API FAudioDeviceWorldDelegates
{
};

// 临时保存虹膜复制系统和桥接器的结构体。
struct FIrisSystemHolder
{
};

// 封装无缝世界漫游的类
class FSeamlessTravelHandler
{
};

// 保存的编辑器视口状态信息
struct ENGINE_API FLevelViewportInfo
{
};

// Tick函数，启动物理时钟
struct FStartPhysicsTickFunction : public FTickFunction
{
};

// 结束物理时钟的Tick函数
struct FEndPhysicsTickFunction : public FTickFunction
{
};

// 传递给SpawnActor函数的可选参数结构体。
struct ENGINE_API FActorSpawnParameters
{
};

// 世界参与者生成辅助函数
struct ENGINE_API FActorSpawnUtils

    /* *
     *这封装了世界的异步跟踪功能。它包含跟踪数据缓冲区的两个缓冲区，并对每个时钟周期交替使用。
     *
     *您可以使用以下api来使用异步跟踪:AsyncLineTrace, AsyncSweep, AsyncOverlap
     *当你使用这些api时，它将被保存到AsyncTraceData
     * fworldasynctracestate包含两个缓冲区来旋转每个帧，因为您可能需要在下一帧中获得结果
     *但是，如果你在下一帧还没有得到结果，结果将被丢弃。
     *如果你想在可用时立即获得结果，请使用Delegate。
     */
    struct ENGINE_API FWorldAsyncTraceState
{
};

/* FAsyncPreRegisterDDCRequest -在注册组件之前我们将要等待的异步DDC请求的信息*/
class ENGINE_API FAsyncPreRegisterDDCRequest
{
};

/*
 *在UWorld中包含特定ELevelCollectionType的一组级别
 *以及正确标记/更新这些关卡所需的上下文。这个对象只能移动。
 */
struct ENGINE_API FLevelCollection
{
};

/*
 *一个辅助RAII类，用于在作用域内为特定FLevelCollection设置UWorld上的相关上下文。
 *构造函数将设置PersistentLevel、GameState、NetDriver和DemoNetDriver
 *析构函数会恢复原始值。
 */
class ENGINE_API FScopedLevelCollectionContextSwitch
{
};

// 辅助类允许UWorldPartition广播UWorld事件
struct FWorldPartitionEvents
{
};

// 包含用于初始化世界的可选参数集合的结构体
struct FWorldInitializationValues
{
};

/*
 * World是代表地图或沙盒的顶层对象，其中存在并渲染actor和组件。
 *
 *一个世界可以是一个单一的持久层，带有一个可选的流层列表，这些流层可以通过volume和blueprint函数加载和卸载
 *或者它可以是由世界组成的关卡的集合。
 *
 *在独立游戏中，通常只有一个世界存在，除非在无缝区域转换期间，目的地和当前世界都存在。
 *在编辑器中存在许多世界:正在被编辑的关卡，每个饼图实例，每个具有交互式渲染视口的编辑器工具等等。
 */
class ENGINE_API UWorld final : public UObject, public FNetworkNotify
{
};

// 世界代表
class ENGINE_API FWorldDelegates
{
};

// 辅助结构体，允许ULevelStreaming根据正在加载的流级别更新其世界
struct FWorldNotifyStreamingLevelLoading
{
};