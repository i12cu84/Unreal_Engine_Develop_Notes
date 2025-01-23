P1 Gameplay Tags
Inputs//输入
Abilityes//能力
Attributes//属性
Damage Types//伤害类型
Buffs/Debuffs//增益/减益
Messages//消息
Datas//数据

P2 Creating Gameplay Tags in the Editor
Project Settings -> Project -> GameplayTags -> Gameplay Tag Redirects

项目路径 -> Conifg -> DefaultGameplayTags.ini

P3 Creating Gameplay Tags from Data Tables //从数据表创建游戏标签
Miscellaneous(杂项) -> Data Table(数据表) -> 选择GameplayTagTableRow(游戏标签表行)
以"DT_" 开头 

P4 Missing

P5 Apply Gameplay Tags with Effects //使用效果应用游戏标签
GrabtedTags //游戏标签
授予标签只有在效果具有持续时间时才有意义
效果消失时,标签就被移除了
建议:研究一下GAS的AbilitySystemComponent.h源文件(有相关API以及注释文档)
|Replication Mode|Use Case|Description|
|:---:|:---:|:---:|
|FulL|Single Player|Gameplay Effects are replicated to all clients|
|Mixed|Multiplayer,Player-Controlled|Gameplay Effects are replicated to the owning client only. Gameplay cues and Gameplay Tags replicated to all clients.|
|Minimal|Multiplayer, Al-Controlled|Gameplay Effects are not replicated, Gameplay Cues and Gameplay Tags replicated to all clients.|
翻译:
|复制模式|用例|描述|
|:---:|:---:|:---:|
|FulL|单机|游戏效果被复制到所有客户端|
|Mixed|多人,玩家控制|游戏效果仅复制到拥有客户端。游戏提示和游戏标签复制到所有客户端。|
|Minimal|多人, AI控制|游戏效果不复制, 游戏提示和游戏标签复制到所有客户端。|

P6 Gameplay Effect Delegates //游戏效果委托

protected:
void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveHandle) override
{
    GEngine->AddOnScreenDebugMessage(1, 8.f, FColor::Blue, TEXT("Effect Applied!"));
    //该方法在效果应用时调用,在拾取特效物品后在UE中打印出"Effect Applied!"
}

P7 Get All Asset Tags //获取所有资产标签

FGameplayTagContainer TagContainer;
EffectSpec.GetAllAssetTags(TagContainer);
for(const FGameplayTags& Tag:TagContainer)
{
    //TODO:Broadcast the tag to the Widget Controller
    const FString Msg=FString::Printf(TEXT("GE Tag: %s"),*Tag.ToString());
    GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, Msg);//-1时,新消息不会替换旧消息,8秒,颜色是蓝色,Msg是消息内容
}

P8 Broadcasting Effect Asset Tags

//非动态多播委托
DECLARE_mULTICAST_DELEGATE_One(FEffectAssetTags, const FGameplayTagContainer& /*AssetTags*/);

FEffectAssetTags EffectAssetTags;

EffectAssetTags.Broadcast(TagContainer);

Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.Addlambda(
    [](const FGameplayTagContainer& AssetTags)
    {
        const FString Msg=FString::Printf(TEXT("GE Tag: %s"),*Tag.ToString());
        GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, Msg);//-1时,新消息不会替换旧消息,8秒,颜色是蓝色,Msg是消息内容
    }
);

P9 UI Widget Data Table
STRUCT(BlueprintType)
struct FUIWidgetRow:public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    FGameplayTag HessageTag=FGameplayTag();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    FText Message=FText();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UAuraUserWidget> MessageWidget;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    UTexture2D* Image=nullptr;
}

//细节面板中将会显示该物体的获取
UPROPERTY(EditDefaultOnly,BlueprintReadOnly, Category = "Widget Data")
TObjectPtr<UDataTable> MessageWidgetDataTable;  

P10 Retrieving Rows from Data Tables
细节面板中设计数据表

template<typename T>
T* GetDataTableRowByTag(const UDataTable* DataTable, const FGameplayTag& Tag)
{
    return DataTable->FindRow<T>(Tag.GetTagName(),TEXT(""));
}

GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable,Tag);

P11 Broadcasting Data Table Rows //广播数据表行
MessageWidgetRowDelegate.Broadcast(*Row);

FGameplayTag MessageTag=FGameplay::RequestGameplayTag(FName("Message"));
if(Tag.MatchesTag(MessageTag))
{
    FUIWidgetRow* Row=GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable,Tag);
    MessageWidgetRowDelegate.Broadcast(*Row);
}

P12 Message Widget 制作一个信息窗口
用到Widget 
HorizontalBox组件 横向排布Widget
Spacer组件 空白

对HB组件右键 -> Wrap With -> Overlay //作用:禁止窗口拉伸

P13 Animating the Message Widget 动画信息窗口
为widget创建Sequencer,widget窗口左下角动画可激活

P14 Replacing Callbacks with Lambdas
//当HealthAttribute改变时,OnHealthChanged广播Data.NewValue
AbilitySystemComponent->GetGameplayAttributeValutChangeDelegate(
    AuraAttributeSet->GetHealthAttribute()).AddLambda(
    [](const FOnAttributeChangeData& Data)
    {
        OnHealthChanged.Broadcast(Data.NewValue);
    }
);
//当HealthAttribute改变时,OnHealthChanged广播Data.NewValue
AbilitySystemComponent->GetGameplayAttributeValutChangeDelegate(
    AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
    [](const FOnAttributeChangeData& Data)
    {
        OnMaxHealthChanged.Broadcast(Data.NewValue);
    }
);

//当HealthAttribute改变时,OnHealthChanged广播Data.NewValue
DELCARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature,float,NewValue)

UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
FOnAttributeChangedSignature OnHealthChanged;

UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
FOnAttributeChangedSignature OnMaxHealthChanged;

(存在红色节点时)蓝图 -> Refresh Nodes 刷新节点

P15 Ghost Golbe 幽灵球,渐进扣除和恢复能量条
ProgressBar组件使用方法
Event Tick右键 -> Add Call to Parent Function(右键呼出父类函数)

P16 Properly Clamping Attributes //正确地限制属性
出现了bug:当拾取恢复药剂后生命恢复满时触碰自伤火焰失去扣血效果

//夹住中间并获得最大健康值
GetHealth(FMath::Clamp(GetHealth(),0.f,GetMaxHealth()));