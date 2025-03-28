P1 Game UI Architecture UI系统架构

P2 Aura User Widget and Widget Controller 用户控件和控件控制器
启用User Widget 蓝图模板
启用Object蓝图 构建Widget Controller
UFUNCTION(BlueprintCallable) // 蓝图可调用
void SetWidgetController(UObject* InWidgetController)  //设置控件控制器
{
    WidgetController=InWidgetController;
    WidgetControllerSet();
}
UPROPERTY(BlueprintReadOnly) // 蓝图只读
TObjectPtr<UObject> WidgetController;
UFUNCTION(BlueprintImplementableEvent) // 蓝图可实现事件,在蓝图中将会变成"Event Widget Controller Set"事件
void WidgetControllerSet();

UPROTERTY(BlueprintReadOnly,Category="WidgetController") // 蓝图只读
TObjectPtr<APlayerController> PlayerController; //玩家控制器

P3 Globe Progress Bar 全局进度条
UMG的蓝图使用介绍

P4 Health Globe 血条蓝图

P5 Aura HUD
HUD作为Widget的容器
UPROPERTY()
TObjectPtr<UAuraUserWidget> OverlayWidget; //覆盖控件
UPROPERTY(EditAnywhere) // 可在任何地方编辑(包括继承后成为蓝图时的细节面板中)
TSubclassOf<UauraUsetWidget> OverlayWidgetClass; //覆盖控件类

UUserWidget * Widget=CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);//创建覆盖控件
Widget->AddToViewport(); //添加到视口

P6 Overtlay Widget Controller
USTRUCT(BlueprintType) // 蓝图类型
struct FWidgetControllerParams
{
    GENERATED_BODY()
    FWidgetControllerParams(){}
    FWidgetControllerParams(APlayerController* PC, APlayerState* PS,UAbilitySystemComponent* ASC,UAraAttributeSet* AS):PlayerController(PC),PlayerState(PS),AbilitySystemComponent(ASC),AttributeSet(AS){}

    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    TObjectPtr<APlayerController> PlayerController=nullptr;

    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    TObjectPtr<APlayerState> PlayerState=nullptr;

    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent=nullptr;

    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    TObjectPtr<UAraAttributeSet> AttributeSet=nullptr;
}

UPROPERTY(BlueprintCallable) // 蓝图可调用
void SetWidgetControllerParams(const FWidgetControllerParams& WCParams)//设置控件控制器参数
{
    PlayerController=WCParams.PlayerController;
    PlayerState=WCParams.PlayerState;
    AbilitySystemComponent=WCParams.AbilitySystemComponent;
    AttributeSet=WCParams.AttributeSet;
}

UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams) // 获取覆盖控件控制器
{
    if(OverlayWidgetController==nullptr)
    {
        OverlayWidgetController=NewObeject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
        OverlayWidgetController->SetWidgetControllerParams(WCParams);

        //return OverlayWidgetController;
    }
    return OverlayWidgetController;
}

UPROPERTY()
TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAraAttributeSet* AS)
{
    checkf(OverlayWidgetClass,TEXT("Overlay Widget Class uninitialized,please fill out BP_AuraHUD"));//检查覆盖控件类是否初始化
    checkf(OverlayWidgetControllerClass,TEXT("Overlay Widget Controller Class uninitialized,please fill out BP_AuraHUD"));//检查覆盖控件控制器类是否初始化

    UUserWidget * Widget=CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);//创建覆盖控件

    OverlayWidget =Cast<UAuraUserWidget>(Widget);//转换为覆盖控件

    const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);//玩家控制器,玩家状态,能力系统组件,属性集
    UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);//获取覆盖控件控制器

    OverlayWidget->SetWidgetController(WidgetController);//设置覆盖控件控制器

    Widget->AddToViewport(); //添加到视口
}

-> 多人游戏,其他客户端的PlayerController都是空指针,这方法不会调用
if(AAuraPlayerController* AuraPlayerController=Cast<AAuraPlayerController>(GetController()))
{
    if(AAuraHUD* AuraHUD=Cast<AAuraHUD>AuraPlayerController->GetHUD())
    {
        AuraHUD->InitOverlay(AuraPlayerController,AuraPlayerState,AbilitySystemComponent,GetAttributeSet);
    }
}

->
if(Subsystem)
{
    SubSystem->AppMappintContext(AuraContext,0);
}

P7 Broadcasting Intial Values 广播初始值
DECLARE_MULTICAST_DELEGATE(FOnHealtChangeSignature,float,NewHealth);//声明动态多播委托

virtual void BroadcastInitialValues() override//广播初始值,注意基类要有纯虚函数
{
    const UAureAttributeSet* AuraAttributeSet=CastChecked<UAuraAttributeSet>(AttributeSet);//转换为属性集

    OnHealthChange.Broadcast(AuraAttributeSet->GetHealth());//广播初始值
    OnMaxHealthChange.Broadcast(AuraAttributeSet->GetMaxHealth());//广播初始值
}

UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")//BlueprintAssignable是蓝图可赋值(可分配蓝图)
FOnHealthChangeSignature OnHealthChange;//声明多播委托

P8 Listening for Attribute Changes
virtual void BindCallbacksToDependencies() override//绑定依赖关系
{
    const UAuraAttributeSet* AuraAttributeSet=CastChecked<UAuraAttributeSet>(AttributeSet);//转换为属性集
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddUObject(this,&UAuraAbilitySystemComponent::HealthChange);//获取游戏属性值改变委托,添加健康改变回调
}

void HealthChange(const FOnAttributeChangeData& Data) const//健康改变
{
    OnHealthChange.Broadcast(Data.NewValue);//广播健康改变
}

OverlayWdigetController->BindCallbacksToDependencies();//绑定依赖关系

void BindAttributeChangeCallbacks();//绑定属性改变回调

P9 Callbacks for Mana Changes
与Health变更同理