P1 Attributes - 属性
Prediction: The client
doesn't need to wait for the
server's permission to
change a value. The value
can change immediately
client-side and the server is
informed of the change. The
server can roll back
changes that are invalid.
翻译:预测: 客户端不需要等待服务器的许可来改变一个值。该值可以立即在客户端改变，并且服务器被告知该值已改变。服务器可以回滚无效的更改。

P2 Health and Mana - 生命值和魔法值
UPROPERTY(BlueprintReadOndly,ReplicatedUsing=OnRep_Health,Category="Vital Attributes) //BlueprintReadOnly表示在蓝图上只读，ReplicatedUsing表示使用OnRep_Health函数同步,当该属性改变时，(服务器)会自动同步到客户端,Category表示在蓝图上显示的类别
FGameplayAttributeData Health; //生命值

UFUNCTION() //客户端调用该函数，会自动同步到服务器
void OnRep_Health(const FGameplayAttributeData& OldValue) const//当服务器同步生命值到客户端时，会调用这个函数
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Health, OldValue); //通知游戏系统，生命值已经改变
}
void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps([&]OutLifetimeProps);//调用父类的GetLifetimeReplicatedProps函数,[&]的作用是引用传递
    DOREPLIFETIME(UAuraAttributeSet, Health,COND_None,REPNOTIFY_Always); //生命值需要同步,COND_None表示不需要条件，REPNOTIFY_Always表示每次改变都通知
}

P3 Attribute Accessors - 属性访问器
UPROPERTY(BlueprintReadOndly,ReplicatedUsing=OnRep_Health,Category="Vital Attributes) //不做更改
FGameplayAttributeData Health; //不做更改
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAuraAttributeSet,Health) //定义一个获取生命值的函数

UAuraAttributeSet()//类中的构造函数 初始化
{
    InitHealth(100.f); //初始化生命值为100
}

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)\
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
//这个宏是为了方便定义属性访问器，比如生命值，魔法值，攻击力等

console command //控制台命令
->showdebug abilitysystem  //显示调试能力系统 显示头像蓝图角色属性等 按翻页键会显示下一个

P4 Effect Actor - 效果演员 使用Actor蓝图基类
Mesh=CreateDefaultSubobject<UStaticMeshComponent>("Mesh"); //创建一个静态网格组件
SetRootComponent(Mesh); //设置根组件为静态网格组件

Sphere=CreateDefaultSubobject<USphereComponent>("Sphere"); //创建一个球体组件
Sphere->SetupAttachment(GetRootComponent()); //将球体组件附加到根组件上

UFUNCTION()
virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override //当重叠时调用
{
    if(IAbilitySystemInterface* ASCInterface=Cast<IAbilitySystemInterface>(OtherActor))
    {
        //TODO: Change this to apply a Gameplay Effect.For now,using const_cast as a hack.
        const UAuraAttributeSet* AuraAttributeSet=Cast<UAuraAttributeSet>(         ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass())); //获取其他角色的属性集
        UAuraAttributeSet* MutableAuraAttributeSet=const_cast<UAuraAttributeSet*>(AuraAttributeSet); //将const_cast转换为非const
        AuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth()+25.f); //增加其他角色的生命值
        Destroy(); //销毁自己
    }
}

virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override //当结束重叠时调用
{

}

//调用它
Sphere->OnComponentBeginOverlap.AddDynamic(this, &AEffectActor::OnOverlap); //当球体组件开始重叠时调用OnOverlap函数
Sphere->OnComponentEndOverlap.AddDynamic(this, &AEffectActor::EndOverlap); //当球体组件结束重叠时调用EndOverlap函数

制作出血瓶用于触发回复效果