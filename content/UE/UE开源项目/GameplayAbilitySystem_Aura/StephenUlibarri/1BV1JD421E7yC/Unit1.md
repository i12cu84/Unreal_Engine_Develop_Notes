[P1-P200](https://www.bilibili.com/video/BV1JD421E7yC)

P1 Introduction(介绍)
GAS(Gameplay Ability System)游戏能力系统教程最佳实践
旨在设计需要管理属性的游戏项目
遵循行业最佳实践,游戏项目设计可扩展

P1 Project Creation
Editor Perferences
-> 
Souce Code Editor(设置源码编辑器)
Enable Live Coding (启用实时编码)取消
Automatically Compile Newly Added C++ Classes (自动编译新添加的C++类 热重载)取消
Asset Editor Open Location -> Main Window (设置资源编辑器打开位置)

P2 Setting up Version Control
git上编辑可忽略的文件
```文件名.gitignore(该文件用于git上传时屏蔽相关上传的文件)
Binaries
DerivedDataCache
Intermediate
Saved
Build
Content
**/BlackAlder
**/Landscape
**/MedievalDungeon
**/Megascans
**/starterContent
**/Assets 

.vscode
.vs
*.VC.db
*.opensdf
*.opendb
*.sdf
*.sln
*.suO
*.xcodeproj
*.xcworkspace
```
git status 查看暂存文件

P3 The Base Character Class
编辑器符号(Editor symbols for debugging) -> 可以进行调试程序
```VS配置
DebugGame（直接以全屏方式运行你默认地图的游戏，可以调试，无法编辑蓝图）
DebugGame Editor（打开debug工程，可以编辑保存蓝图，可以调试信息）
Development（直接运行默认地图游戏，无法调试，无法修改蓝图）、Development Editor（可以修改蓝图，无法调试）
```

P4 Player and Enemy Characters
UCLASS(Abstract) ->指明是抽象基类，是不能被直接创建出来的。需要创建子类，子类可以创建实例
当对源代码文件夹发生改动时,需要删除Binaries和Intermediate文件夹重新编译解决方案

P5 Character Blutprint Setup 加装人物基础上的武器插槽模型
骨骼网格体插槽指针TObjectPtr指针类型(功能:如访问跟踪(可以被访问或取消引用的频率)和可选的延迟加载功能(实际需要时才加载资产))
构建基类后在Editor中创建蓝图以以继承基类
Weapon=CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");//创建一个武器插槽
Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));//将武器插槽与人物插槽绑定 注意在蓝图中创建的插槽名称需要与WeaponHandSocket一致
Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);//设置武器插槽不进行碰撞检测 

P6 Animation Blueprints 人物状态机(蓝图)编辑
Animation -> Animation Blueprints -> 创建一个动画蓝图
State machine -> 创建一个状态机
Slot 'DefeatSlot' -> 创建一个插槽
蓝图变量右键(Convert to Validated Get(转换为有效的Get)) -> 转换为验证的获取
Blendspace Payer -> 创建一个混合空间播放器(用于通用的动画混合)

P7 Enhanced Input 增强输入系统
Input -> Input Actions -> 创建一个增强输入系统
Input -> Input Mapping Context -> 创建一个输入映射上下文
Modifiers 
-> Negate(否定修饰符)(打勾的轴位取反)
-> Swizzle Input Axis Values(交换输入轴值) YXZ(交换原有XYZ轴位改变,第一数是Y轴位,第二数是X轴位,第三数是Z轴位)

P8 Aura Player Controller 玩家控制器 增强输入 -> 关联
bReplicates=true; -> 设置为true，即指定为参与复制的实体。在服务器端和客户端之间进行复制,在多人游戏中，复制基本上是指一个实体在服务器上发生变化时，该变化将被复制或发送连接到服务器的所有客户端。
Super::BeginPlay(); -> 调用父类的BeginPlay函数
EnhancedInput增强输入模块名字（输入到build.cs中）
check(AuraContext); 在没有设置的情况下运行游戏，会崩溃
UEnhancedInputLocalPlayerSubsystem* Subsystem = UlocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()); -> 获取本地玩家的增强输入子系统
check(Subsystem); -> 检查是否获取成功
Subsystem->AddMappingContext(AuraContext,0); -> 添加输入映射上下文,0代表优先级

bShowMouseCursor=true; -> 设置鼠标可见
DefaultMouseCursor=EMouseCursor::Default; -> 设置鼠标样式

FInputModeGameAndUI InputModeData-> 设置鼠标和键盘都可以使用
InputModeData.SetLockMouseToViewporBehavior(EMouseLockMode::DoNotLock); -> 设置鼠标不锁定到视口
InputModeData.SetHideCursorDuringCapture(false); -> 设置鼠标不隐藏
SetInputMode(InputModeData); -> 设置输入模式

P9 Movement Input 移动输入
UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent); -> CastChecked(断言):强制转换检测,如果转换失败则崩溃
UPROPERTY(EditAnywhere,Category="Input") -> EditAnywhere(编辑任何地方),Category(分类)

EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move); -> 绑定移动动作 MoveAction是移动动作,ETriggertEvent::Triggered是触发事件,Move是移动函数(自定义)

FRotator YawRotation = FRotator(0.f, Roration.Yaw, 0.f); -> 创建一个旋转角度,0.f表示X轴旋转角度,Rotation.Yaw表示Y轴旋转角度,0.f表示Z轴旋转角度
FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); -> 获取旋转矩阵的X轴单位向量
FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); -> 获取旋转矩阵的Y轴单位向量

if(APawn* COntrolledPawn = GetPawn<APawn>();) -> 获取控制的角色
{
    ControlledPawn->AddMovementInput(ForwardVector, InputAxisVector.Y); -> 添加Y移动输入
    ControlledPawn->AddMovementInput(RightVector, InputAxisVector.X); -> 添加X移动输入
}

P10 Game Mode
GetCharacterMovement()->bOrientRotationToMovement=true; -> 设置角色移动时自动旋转
GetCharacterMovement()->RotationRate=(FRotator(0.f, 400.f, 0.f)); -> 设置角色旋转速度
GetCharacterMovement()->bConstrainToPlane=true; -> 设置角色只能沿平面移动
GetCharacterMovement()->bSnapToPlaneAtStart=true; -> 设置角色开始时自动贴合平面

bUseControllerRotationPitch=false; -> 设置角色不使用控制器旋转Pitch
bUseControllerRotationRoll=false; -> 设置角色不使用控制器旋转Roll
bUseControllerRotationYaw=false; -> 设置角色不使用控制器旋转Yaw


P11 Enemy Interface 敌人接口
Unreal Interface蓝图 -> 创建一个接口
纯虚函数 抽象类,必须在继承的类中实现(接口重写)

P12 Highlight Enemies
FHitReuslt CursorHit; -> 创建一个碰撞结果
GetHitResultUnderCursor(ECC_Visibility,false,CursorHit); -> 获取鼠标位置下的碰撞结果
if(!CursorHit.bBlockingHit) return ;-> 如果没有碰撞到任何东西

lastActor=ThisActor; -> 将当前碰撞到的角色赋值给lastActor
ThisActor=Cast<IEnemyInterface>(CursoHit.GetActor()); -> 将当前碰撞到的角色转换为敌人接口

if(LastActor==nullptr)
{
    if(ThisActor!=nullptr)
    {
        ThisActor->HighlightActor();
    }
    else
    {
        //do nothing
    }
}
else
{
    if(ThisActor==nullptr)
    {
        LastActor->UnHighlightActor();
    }
    else
    {
        if(LastActor!=ThisActor)
        {
            LastActor->UnHighlightActor();
            ThisActor->HighlightActor();
        }
        else
        {
            //do nothing
        }
    }
}
->
A. LastActor null && ThisActor null
    do nothing
B. LastActor null && ThisActor not null
    ThisActor->HighlightActor();
C. LastActor not null && ThisActor null
    LastActor->UnHighlightActor();
D. LastActor not null && ThisActor not null && LastActor==ThisActor
    do nothing
E. LastActor not null && ThisActor not null && LastActor!=ThisActor
    LastActor->UnHighlightActor();
    ThisActor->HighlightActor();

P13 Post Process Highlight
PostProcessComponent->Settings.ColorGrading.Shadows=ShadowColor; -> 设置阴影颜色

P13 Post Process Highlight 后期处理盒子(高亮)
-> Post Process Volume 细节面板
PostProcessVolume-> Infinite Extent(Unbound) -> 设置后期处理盒子的范围(勾选,无限范围)
Post Process Materials -> 添加后期处理材料

-> Project Setting
Cusotm Depth-Stencil Pass -> Enable with Stencil 启用带有模板的自定义深度模板通道

->BP_Character ->Mesh
Render CustomDepth Pass 启用高亮
CustomDepth Stencil Value 自定义深度模板值

GetMesh()->SetRenderCustomDepth(true); -> 设置自定义深度模板值
GetMesh()->CustomDepthStencilValue(250.f); -> 设置自定义深度模板值