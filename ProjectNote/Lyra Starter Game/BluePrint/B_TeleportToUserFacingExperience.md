传送台蓝图

Event Begin ->
Widget -> Set Tick Mode (Disabled) // 禁用Tick计时器
Is Default Experience // [推测]用于初始化判断

LoadIntoExperience ->
Push Content to Layer for Player // [推测]初始化内容

Create Hosting Request // 发起一个游戏会话的请求
```cpp
// C:\Users\chru\Desktop\Lyra\Source\LyraGame\GameModes\LyraUserFacingExperienceDefinition.cpp
// Epic Games, Inc.版权所有版权所有。(本节全部代码解析仅用做技术交流,后续不再赘述,侵权联系删除)

#include "LyraUserFacingExperienceDefinition.h"

#include "CommonSessionSubsystem.h"
#include "CommonUISettings.h"
#include "Containers/UnrealString.h"
#include "ICommonUIModule.h"
#include "NativeGameplayTags.h"
#include "UObject/NameTypes.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LyraUserFacingExperienceDefinition)

// 定义Lyra::Experience命名空间内的TAG_Platform_Trait_ReplaySupport游戏玩法标签
namespace Lyra::Experience
{
    UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_Platform_Trait_ReplaySupport, "Platform.Trait.ReplaySupport");
};

// UE_DEFINE_GAMEPLAY_TAG_STATIC宏用于定义一个静态的游戏玩法标签
// 它允许开发者创建具有唯一名称和描述的标签，这些标签可以用于分类和识别游戏中的不同特性

// 定义一个成员函数CreateHostingRequest，返回UCommonSession_HostSessionRequest类型的指针
UCommonSession_HostSessionRequest* ULyraUserFacingExperienceDefinition::CreateHostingRequest() const
{
    // 将ExperienceID.PrimaryAssetName转换为字符串，并存储在ExperienceName常量中
    const FString ExperienceName = ExperienceID.PrimaryAssetName.ToString();
    // 将GetPrimaryAssetId().PrimaryAssetName转换为字符串，并存储在UserFacingExperienceName常量中
    const FString UserFacingExperienceName = GetPrimaryAssetId().PrimaryAssetName.ToString();
    // 通过NewObject函数创建UCommonSession_HostSessionRequest类型的全新实例
    UCommonSession_HostSessionRequest* Result = NewObject<UCommonSession_HostSessionRequest>();
    // 设置Result对象的OnlineMode属性为Online，指示会话在线状态
    Result->OnlineMode = ECommonSessionOnlineMode::Online;
    // 设置Result对象的bUseLobbies属性为true，表示会话将使用大厅
    Result->bUseLobbies = true;
    // 将MapID赋值给Result对象的MapID属性
    Result->MapID = MapID;
    // 将UserFacingExperienceName赋值给Result对象的ModeNameForAdvertisement属性
    Result->ModeNameForAdvertisement = UserFacingExperienceName;
    // 将ExtraArgs赋值给Result对象的ExtraArgs属性
    Result->ExtraArgs = ExtraArgs;
    // 向Result对象的ExtraArgs添加键值对，键为"Experience"，值为ExperienceName
    Result->ExtraArgs.Add(TEXT("Experience"), ExperienceName);
    // 将MaxPlayerCount赋值给Result对象的MaxPlayerCount属性
    Result->MaxPlayerCount = MaxPlayerCount;

    // 检查ICommonUIModule::GetSettings()返回的对象是否包含Lyra::Experience::TAG_Platform_Trait_ReplaySupport标签
    if (ICommonUIModule::GetSettings().GetPlatformTraits().HasTag(Lyra::Experience::TAG_Platform_Trait_ReplaySupport.GetTag()))
    {
        // 如果bRecordReplay为true，向Result对象的ExtraArgs添加键值对，键为"DemoRec"，值为空字符串
        if (bRecordReplay)
        {
            Result->ExtraArgs.Add(TEXT("DemoRec"), FString());
        }
    }

    // 函数返回Result对象，即新创建的UCommonSession_HostSessionRequest实例
    return Result;
}

/*
提取体验名称：
ExperienceID.PrimaryAssetName被转换为字符串，并存储在ExperienceName常量中。
GetPrimaryAssetId().PrimaryAssetName被转换为字符串，并存储在UserFacingExperienceName常量中。
创建请求对象：
使用NewObject<UCommonSession_HostSessionRequest>()创建一个UCommonSession_HostSessionRequest类型的全新实例，并将其存储在Result指针中。
设置请求属性：
Result->OnlineMode被设置为ECommonSessionOnlineMode::Online，指示会话是在线状态。
Result->bUseLobbies被设置为true，表示会话将使用大厅。
Result->MapID被赋值为MapID。
Result->ModeNameForAdvertisement被赋值为UserFacingExperienceName。
Result->ExtraArgs被赋值为ExtraArgs。
Result->ExtraArgs添加了一个键值对，键为"Experience"，值为ExperienceName。
Result->MaxPlayerCount被赋值为MaxPlayerCount。
检查回放支持：
检查ICommonUIModule::GetSettings()返回的对象是否包含Lyra::Experience::TAG_Platform_Trait_ReplaySupport标签。
如果bRecordReplay为true，并且平台支持回放，则向Result->ExtraArgs添加一个键值对，键为"DemoRec"，值为空字符串。
返回请求对象：
函数最终返回Result对象，即新创建的UCommonSession_HostSessionRequest实例。
*/
```

Common Session Subsystem -> Host Session // 处理游戏会话创建的请求
```cpp
// C:\Users\chru\Desktop\Lyra\Plugins\CommonUser\Source\CommonUser\Private\CommonSessionSubsystem.cpp
void UCommonSessionSubsystem::HostSession(APlayerController* HostingPlayer, UCommonSession_HostSessionRequest* Request)
{
    // 检查Request是否为nullptr，如果是，则设置创建会话的错误
    if (Request == nullptr)
    {
        SetCreateSessionError(NSLOCTEXT("NetworkErrors", "InvalidRequest", "HostSession passed an invalid request."));
        OnCreateSessionComplete(NAME_None, false);
        return;
    }

    // 根据HostingPlayer获取LocalPlayer对象，如果为nullptr且不是专用服务器，则设置错误并返回
    ULocalPlayer* LocalPlayer = (HostingPlayer != nullptr) ? HostingPlayer->GetLocalPlayer() : nullptr;
    if (LocalPlayer == nullptr && !bIsDedicatedServer)
    {
        SetCreateSessionError(NSLOCTEXT("NetworkErrors", "InvalidHostingPlayer", "HostingPlayer is invalid."));
        OnCreateSessionComplete(NAME_None, false);
        return;
    }

    // 验证请求是否有效，如果无效，则设置错误并返回
    FText OutError;
    if (!Request->ValidateAndLogErrors(OutError))
    {
        SetCreateSessionError(OutError);
        OnCreateSessionComplete(NAME_None, false);
        return;
    }

    // 如果请求的在线模式是离线，则根据当前世界的网络模式进行判断
    if (Request->OnlineMode == ECommonSessionOnlineMode::Offline)
    {
        // 如果当前世界是在客户端模式下运行，则设置错误并返回
        if (GetWorld()->GetNetMode() == NM_Client)
        {
            SetCreateSessionError(NSLOCTEXT("NetworkErrors", "CannotHostAsClient", "Cannot host offline game as client."));
            OnCreateSessionComplete(NAME_None, false);
            return;
        }
        else
        {
            // 如果是在服务器模式下运行，则立即使用构造的旅行URL来服务器旅行
            GetWorld()->ServerTravel(Request->ConstructTravelURL());
        }
    }
    else
    {
        // 如果请求的在线模式不是离线，则创建在线会话
        CreateOnlineSessionInternal(LocalPlayer, Request);
    }
}

/*
参数检查：
检查Request参数是否为nullptr，如果是，则设置创建会话的错误，并结束函数执行。
如果HostingPlayer不为nullptr，则获取对应的LocalPlayer对象；如果HostingPlayer为nullptr或游戏不是专用服务器，则设置错误并结束函数执行。
请求验证：
调用Request对象的ValidateAndLogErrors方法来验证请求是否有效，并将验证错误记录在OutError中。
如果验证失败，则设置创建会话的错误，并结束函数执行。
判断在线模式：
检查Request对象的OnlineMode是否为Offline。
如果是离线模式，并且当前世界是在客户端模式下运行，则设置错误并结束函数执行。
如果是离线模式但当前世界是在服务器模式下运行，则立即使用Request对象构造的旅行URL来服务器旅行。
如果在线模式不是离线，则创建在线会话。
会话创建：
如果请求有效，并且世界是在正确的网络模式下，函数将尝试创建会话。
创建会话的具体实现是在CreateOnlineSessionInternal函数中，这个函数接受LocalPlayer和Request作为参数。
*/
```