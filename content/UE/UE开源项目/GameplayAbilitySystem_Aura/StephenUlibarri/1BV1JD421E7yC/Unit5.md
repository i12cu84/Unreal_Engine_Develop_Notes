P1 Gameplay Effects 
Gameplay Effects游戏效果
Data only仅数据
Don't subclass UGameplayEffect 不要子类化 UGameplayEffect
Change Attributes through:通过以下方式更改属性：
Modifiers修饰符
Executions执行

Modifier Op修饰符操作
Add添加
Multiply乘法
Divide除法
Override覆盖

Magnitude Calculation Type幅度计算类型
Scalable Float可缩放浮点数
Attribute Based基于属性
Custom Calculation class (MMC)自定义计算类（MMC）
Set by Caller由调用者设置

Executions执行
Gameplay游戏
Effect效果
Execution执行
Calculation计算

Gameplay Effects游戏效果
Duration Policy持续时间策略
Instant瞬间
Has Duration有持续时间
Infinite无限
Stacking堆叠
Add Gameplay Tags添加游戏标签
Grant Abilities授予能力

P2 Effect Actor Improved
SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent")));//设置根组件
TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;//瞬间游戏效果类,这会在蓝图的细节面板中显示相关选项

UFUNCTION(BlueprintCallable)
void ApplyEffectToTarget(AActor* Target,TSubclassOf<UGameplayEffect> GameplayEffectClass)//应用效果到目标
{
    /*
    IAbilitySystemInterface* ASCInterface=Cast<IAbilitySystemInterface>(Target);
    if(ASCInterface)
    {
        ASCInterface->GetAbilitySystemComponent();
        UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
    }
    */
    UAuraAbilitySystemComponent* TargetASC= UAbilitySystemBlutprintLibrary::GetAbilitySystemComponent(Target);
    if(TargetASC==nullptr)return;//如果目标ASC为空则返回

    check(GameplayEffectClass);//检查游戏效果类
    FGameplayEffectContextHandle TargetASC->MakeEffectContext();//创建上下文
    EffectContextHandle.AddSourceObject(this);//添加源对象

    FGameplayEffectSpecHandle EffectSpecHandle=TargetASC->MakeOutgoingSpec(GameplayEffectClass,1.f,EffectContextHandle)//创建规范
    TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());//应用游戏效果规范到自身
    //允许蓝图生成一次游戏效果规范,并通过句柄引用它,以便多次应用于多个目标等
}

P3 Instant Gameplay Effects 游戏玩法子类化 - 瞬时游戏效果
以GamepalyEffect蓝图基类
"GE_"代表游戏效果
制作生命/魔力药水

P4 Duration Gameplay Effects 持续时间游戏效果
Actor -> Get Ability System Component(获取能力系统组件) -> Make Effect Context(创建效果上下文) -> GetSourceObject(获取源对象)
Actor -> Get Ability System Component(获取能力系统组件) -> Make Outgoing Spec(创建规范),Level(设置级别),Context(上下文句柄)
Actor -> Get Ability System Component(获取能力系统组件) -> ApplyGameplayEffectSpecToSelf(应用游戏效果规范到自身)
等价->
Apply Effect to Target

P5 Periodic Gameplay Effects 周期性游戏效果
类似药瓶持续恢复生命的效果  

P6 Effect Stacking 效果堆叠
触发多次后期望:只是增加持续时间而不是增加累加的数量
Gameplay Effect Stacking游戏效果堆叠
```
Stacking Type -> Aggregate by Target 堆叠类型"来源"(最多同时回复Count次)

Stack Limit Count 堆叠限制计数

Stack Duration Refresh Policy -> Refresh on Successful Application 堆叠持续时间刷新策略"在成功应用时刷新"
Stack Duration Refresh Policy -> Never Refresh堆叠持续时间刷新策略"从不刷新"

Stack Period Reset Policy -> Reset on Successful Application堆叠周期重置策略"在成功应用时重置"
Stack Period Reset Policy -> Never Reset堆叠周期重置策略"从不重置"

Stack Expiration Policy -> Clear Entire Stack堆叠过期策略"清除整个堆叠"
Stack Expiration Policy -> Remove Single Stack and Refresh Duration堆叠过期策略"移除单个堆叠并刷新持续时间"
Stack Expiration Policy -> Refresh Duration 堆叠过期策略"刷新持续时间"
```

P7 Infinite Gameplay Effects 无限游戏效果
制作一个碰到后持续受到伤害的火焰
UENUM(BlueprintType)//蓝图类型,会在蓝图的细节面板中显示相关内容
enum class EEffectApplicationPolicy
{
    ApplyOnOverlay,//   在重叠时应用
    AppklyOnEndOverlap,//在结束重叠时应用
    DoNotApply//如果不适用则不做任何事情
};
UPROPERTY(EditAnywhere,BlutprintReadOnly,Category="Applied Effects")
EEffectApplicationPolicy InstantEffectApplicationPolicy=EEffectApplicationPolicy::DoNotApply;//瞬间效果应用策略
UPROPERTY(EditAnywhere,BlutprintReadOnly,Category="Applied Effects")
EEffectApplicationPolicy DurationEffectApplicationPolicy=EEffectApplicationPolicy::DoNotApply;//持续时间效果应用策略
UPROPERTY(EditAnywhere,BlutprintReadOnly,Category="Applied Effects")
EEffectApplicationPolicy InfiniteEffectApplicationPolicy=EEffectApplicationPolicy::DoNotApply;//无限效果应用策略

UENUM(BlueprintType)
enum class EEffectRemovelPolicy
{
    RemoveOnEndOverlap,//在结束重叠时移除
    DoNotRemove//如果不移除则不做任何事情
};
UPROPERTY(EditAnywhere,BlutprintReadOnly,Category="Applied Effects")
EEffectRemovelPolicy InfiniteEffectRemovelPolicy=EEffectRemovelPolicy::RemoveOnEndOverlap;//无限效果移除策略

UFUNCTION(BlueprintCallable) //蓝图可调用
void OnOverlap(AActor* TargetActor);//重叠时调用

UFUNCTION(BlueprintCallable) //蓝图可调用
void OnEndOverlap(AActor* TargetActor);//结束重叠时调用

UPROPERTY(EditAnywhere,BlutprintReadOnly,Category="Applied Effects")
bool bDestroyOnEffectRemoval=false;//在效果移除时销毁

UFUNCTION(BlueprintCallable) //蓝图可调用
void ApplyEffectToTarget(AActor* TargetActor,TSubclassOf<UGameplayEffect> GameplayEffectClass)//应用效果到目标
{
    if(TargetActor==nullptr || GameplayEffectClass==nullptr)
    {
        return;
    }
}

P8 Instant and Duration Application Policy持续时间策略UFUNCTION(BlueprintCallable) //蓝图可调用
void OnOverlap(AActor* TargetActor)//重叠时调用
{
    if(InstantEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnOverlay)
    {
        ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
    }
    if(DurationEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnOverlay)
    {
        ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
    }
    if(InfiniteEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnOverlay)
    {
        ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
    }
}

UFUNCTION(BlueprintCallable) //蓝图可调用
void OnEndOverlap(AActor* TargetActor)//结束重叠时调用
{
    if(InstantEffectApplicationPolicy==EEffectApplicationPolicy::AppklyOnEndOverlap)
    {
        ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
    }
    if(DurationEffectApplicationPolicy==EEffectApplicationPolicy::AppklyOnEndOverlap)
    {
        ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
    }
    if(InfiniteEffectApplicationPolicy==EEffectApplicationPolicy::AppklyOnEndOverlap)
    {
        ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
    }
    if(InfiniteEffectRemovelPolicy==EEffectRemovelPolicy::RemoveOnEndOverlap)
    {
        UAbilitySystemComponent* TargetASC=UAbilitySystemBlutprintLibrary::GetAbilitySystemComponent(TargetActor);
        if(IsValid(TargetASC))return;//如果有效则返回
        
        TArray<FActiveGameplayEffectHandle> HandlesToRemove;
        for(TTuple<FActiveGameplayEffectHandle,UAbilitySystemComponent*> HandlePair:ActiveEffectHandles)
        {
            if(TargetASC==HandlePair.Value)
            {
                TargetASC->RemoveActiveGameplayEffect(HandlePair.Key);//移除活动效果
                HandleToRemove.Add(HandlePair.Key);//添加到要移除的句柄中
            }
        }
        for(FActiveGameplayEffectHandle& Handle:HandlesToRemove)
        {
            ActiveEffectHandles.FindAndRemoveChecked(Handle);//从活动效果句柄中移除
        }
    }
}


P9 Infinite Effect Application and Removal 无限效果应用和移除
const FActiveGameplayEffectHandle ActiveEffectHandle=TargetASC->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get());//应用效果
const bool bIsInfinite=EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy==EGameplayEffectDurationType::Infinite;//是否是无限
if(bIsInfinite && InfiniteEffectRemovelPolicy==EEffectRemovelPolicy::RemoveOnEndOverlap)//如果是无限
{
    ActiveEffectHandle.Add(ActiveEffectHandle,TargetASC);//添加活动效果句柄

}

class UAbilitySystemComponent;//能力系统组件 这句话声明要写出来,不然无法写下方的定义

TMap<FActivegameplayEffectHandle,UAbilitySystemComponent*> ActiveEffectHandles;//活动效果句柄

TargetASC->RemoveActiveGameplayEffect(HandlePair.Key,1);//移除活动效果,移除一次堆叠

P10 PreAttributeChange
virtual void PreAttributeChange(const FGameplayAttribute& Attribute,float& NewValue) override;

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute,float& NewValue)
{
    Super::PreAttributeChange(Attribute,NewValue);

    if(Attribute==GetHealthAttribute())
    {
        NewValue=FMath::Clamp(NewValue,0.f,GetMaxHealth());//限制新值在0到最大生命值之间
        UE_LOG(LogTemp,Warning,TEXT("Health changed to %f"),NewValue);
    }
    if(Attribute==GetMaxHealthAttribute())
    {
        UE_LOG(LogTemp,Warning,TEXT("Max Health %f"),NewValue);
    }
}

PreAttributechange //预属性更改
->Changes to CurrentValue//当前值的变化
    before the change happens//发生更改之前
->Triggered by changes to Attributes//由属性的变化触发
    Attribute Accessors//   属性访问器
    Gameplay Effects//游戏效果
    Does not permanently change the modifier, just the value returned from querying the modifier//不永久更改修饰符，只是从查询修饰符返回的值
->Later operations recalculate the Current Value from all modifiers//稍后操作将重新计算所有修饰符的当前值
    We need to clamp again//我们需要再次限制

P11 PostGameplayEffectExecute 游戏效果执行后
virtual void PostGameplayEffectExecute(const FGameplayEffectHodCallbackData& Data) override;//游戏效果执行后

void PostGameplayEffectExecute(const FGameplayEffectHodCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    /*
    if(Data.EvaluatedData.Attribute==GetHealthAttribute())
    {
        UE_LOG(LogTemp,Warning,TEXT("Health from GetHealth(): %f"),GetHealth());//从GetHealth()获取生命值
        UE_LOG(LogTemp,Warning,TEXT("Nagnitude:%f"),Data.EvaluatedData.Magnitude);//评估数据的大小
    }
    */
    //Source = causer of the effect, Target = target of the effect (owner of this AS)
    const FGameplayEffectContextHandle EffectContextHandle=Data.EffectSpec.GetContext();
    const UAbilitySystemComponent* SourceASC=EffectContextHandle.GetOriginalInstigatorAbilitySystemConponent();

    if(IsValid(SourceASC)&&SourceASC->AbilityActorInfo.IsValid()&&SourceASC->AbilityActorInfor->AvatarActor.IsValid())
    {
        AActor* SourceAvatarActor=SourceASC->AbilityActorInfo->AvatarActor.Get();
        const APlayerController* SourceController=SourceASC->AbilityActorInfor->PlayerController.Get();
        if(SourcePlayerContoller==nullptr && SourceAvatarActor!=nullptr)
        {
            if(APawn* Pawn=Cast<APawn>(SourceAvatarActor))
            {
                SourceController=Pawn->GetController();
            }
        }
        if(SourceController)
        {
            ACharacter* SourceCharacter=Cast<ACharacter>(SourceController->GetPawn());
        }
    }

    if(Data.Target.AbilityActorInfor.IsValid()&&Data.Target.AbilityActorInfo->AvatarActor.IsValid())
    {
        AActor* TargetAvatarActor=Data.Target.AbilityActorInfo->AvatarActor.Get();
        AController* TargetController=Data.Target.AbilityActorInfo->Controller.Get();
        ACharacter* TargetCharacter=Cast<ACharacter>(TargetAvatarActor);
        UAbilitySystemConponent* TargetASC=UAbilitySystemBlueprinterLibrary::GetAbilitySystemComponent(TargetAvatarActor);
    }       
}

USTRUCT()
struct FEffectProperties
{
    GENERATED_BODY()

    FEffectProperties(){}

    FGameplayEffectContextHandle EffectContextHandle;

    UPROPERTY()
    UAbilitySystemConponent* TargetASC=nullptr;

    UPROPERTY()
    AActor* TargetAvatarActor=nullptr;

    UPROPERTY()
    AController* TargetController=nullptr;

    UPROPERTY()
    ACharacter* TargetCharacter=nullptr;

private:
    void SetEffectProperties(const FGameplayEffectModCallbackData& Data,FEffectProperties& Props)const 
    {
        Props.EffectContextHandle=Data.EffectSpec.GetContext();
        Props.SourceASC=Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemConponent();

        if(IsValid(Props.SourceASC)&&Props.SourceASC->AbilityActorInfo.IsValid()&&Props.SourceASC->AbilityActorInfor->AvatarActor.IsValid())
        {
            Props.SourceAvatarActor=Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
            Props.SourceController=Props.SourceASC->AbilityActorInfor->PlayerController.Get();
            if(Props.SourcePlayerContoller==nullptr && Props.SourceAvatarActor!=nullptr)
            {
                if(APawn* Pawn=Cast<APawn>(Props.SourceAvatarActor))
                {
                    Props.SourceController=Pawn->GetController();
                }
            }
            if(Props.SourceController)
            {
                ACharacter* SourceCharacter=Cast<ACharacter>(Props.SourceController->GetPawn());
            }
        }

        if(Data.Target.AbilityActorInfor.IsValid()&&Data.Target.AbilityActorInfo->AvatarActor.IsValid())
        {
            Props.TargetAvatarActor=Data.Target.AbilityActorInfo->AvatarActor.Get();
            Props.TargetController=Data.Target.AbilityActorInfo->Controller.Get();
            Props.TargetCharacter=Cast<ACharacter>(Props.TargetAvatarActor);
            Props.TargetASC=UAbilitySystemBlueprinterLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
        }    
    }
}

void UAuraAttributeSet::PostGamePlayEffectExecute(const FGameEffectModCallbackData& Data)
{
    Super::PostGamePlayEffectExecute(Data);

    FEffectProperties Props;
    SetEffectProperties(Data,Props);
}

P12 Curve Tables for Scalable Floats 可扩展浮点数的曲线表
-> 制作有回复级别设定的方法
Miscellaneous(杂项) -> Curve Tables(曲线表) -> Scalable Floats(可扩展浮点数)Linear

UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
float ActorLevel=1.f;

const FGameplayEffectSpecHandle EffectSpecHandle=Target->MakeOutgoingSpec(GameplayEffectClass,ActorLevel,EffectContextHandle);

在细节面板中设置ActorLevel即可

