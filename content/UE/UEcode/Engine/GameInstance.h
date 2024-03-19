// C:\Program Files\Epic Games\UE_5.2\Engine\Source\Runtime\Engine\Classes\Engine\GameInstance.h

// Line 42
//  EWelcomeScreen， //初始屏幕。用于我们可能还没有登录用户的平台。
//  EMessageScreen， //消息屏幕。用来显示一个消息-例如无法连接到游戏。
//  EMainMenu， //游戏主要前端状态。没有玩法，只有用户/会话管理和UI。
//  EPlaying， //游戏应该是可玩的，或者加载到可玩的状态。
//  shutdown， //游戏正在关闭
//  EUnknown， //未知状态主要用于初始化游戏逻辑对象。

/**当前匹配的可能状态，其中匹配是在单个地图上发生的所有玩法*/
// 定义游戏状态的命名空间
namespace GameInstanceState
{
    // 声明一个常量Playing，表示游戏正在运行的状态
    extern ENGINE_API const FName Playing; // We are playing the game
}

// 声明一个类FOnlineSessionSearchResult，但未给出具体的实现
class FOnlineSessionSearchResult;

/**
 * 通知客户端即将前往新的URL
 *
 * @param PendingURL 旅行URL
 * @param TravelType 旅行类型（绝对、相对等）
 * @param bIsSeamlessTravel 是否无缝旅行
 */
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnPreClientTravel, const FString & /*PendingURL*/, ETravelType /*TravelType*/, bool /*bIsSeamlessTravel*/);
// 定义一个新类型别名FOnPreClientTravelDelegate，它指向了FOnPreClientTravel委托的FDelegate类型
typedef FOnPreClientTravel::FDelegate FOnPreClientTravelDelegate;
// 定义一个动态多播委托FOnPawnControllerChanged，有两个参数，分别是APawn*类型的Pawn和AController*类型的Controller
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPawnControllerChanged, APawn *, Pawn, AController *, Controller);

// 定义一个动态多播委托FOnUserInputDeviceConnectionChange，有三个参数，分别是EInputDeviceConnectionState类型的NewConnectionState，FPlatformUserId类型的PlatformUserId，和FInputDeviceId类型的InputDeviceId
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUserInputDeviceConnectionChange, EInputDeviceConnectionState, NewConnectionState, FPlatformUserId, PlatformUserId, FInputDeviceId, InputDeviceId);
// 定义一个动态多播委托FOnUserInputDevicePairingChange，有三个参数，分别是FInputDeviceId类型的InputDeviceId，FPlatformUserId类型的NewUserPlatformId，和FPlatformUserId类型的OldUserPlatformId
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUserInputDevicePairingChange, FInputDeviceId, InputDeviceId, FPlatformUserId, NewUserPlatformId, FPlatformUserId, OldUserPlatformId);

// UGameInstance PIE操作的结果
struct FGameInstancePIEResult
{
};

// 用于初始化/启动PIE游戏实例的参数
//@TODO:其中一些实际上是互斥的，应该重构(放入结构体中，以便将来更容易实现)
struct FGameInstancePIEParameters
{
};

/* *
 * GameInstance:运行游戏实例的高级管理器对象。
 *在游戏创建时生成，直到游戏实例关闭时才销毁。
 *作为独立游戏运行，将会有一个。
 *运行PIE (play-in-editor)将为每个PIE实例生成一个。
 */
class ENGINE_API UGameInstance : public UObject, public FExec
{
};