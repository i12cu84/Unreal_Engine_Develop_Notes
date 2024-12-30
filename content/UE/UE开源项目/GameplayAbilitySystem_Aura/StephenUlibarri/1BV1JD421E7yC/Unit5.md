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
TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;//瞬间游戏效果类

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
}

P37 14:54 Pause https://www.bilibili.com/video/BV1JD421E7yC