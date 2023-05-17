打包 config+content+basictraining.upoject

选中物体后 按着shift移动物体 视角相对位移

构建->构建光照 描绘静态设定的光的构建

ue4 c++层级结构
    object 存放数据 不能被放置到场景(level)中
    actor 能放置在场景(level)中 可以有视觉表现可以被看到
    pawn 可以被控制器(controller)持有(possess)
    character 有角色移动组件(character movement component) 具有适合角色的封装好的一系列功能

层级包含 package>world>level>actor>actor component

反射与垃圾回收系统
    没有内置 但很重要

创建自定义c++类
MyObject.h
    #pragma once
    #include "CoreMinimal.h"
    #include "UObject/NoExportTypes.h"
    #include "MyObject.generated.h"
    UCLASS(Blueprintable)//反射代码 添加后 可以创建基于...的蓝图类
    class CPP3DP_API UMyObject : public UObject
    {
        GENERATED_BODY()
    public:
        UMyObject();
        //UPROPERTY(BlueprintReadWrite)//蓝图系统可读写 
        UPROPERTY(BlueprintReadOnly, Category = "My Variables")//蓝图系统可读写 
        float MyFloat;
        //UFUNCTION(BlueprintCallable)
        UFUNCTION(BlueprintCallable, Category = "My Functions")
        void MyFunction();
    };

MyObject.cpp
    #include "MyObject.h"
    UMyObject::UMyObject() {
        MyFloat = 0.0f;
    }
    void UMyObject::MyFunction() {
        UE_LOG(LogTemp, Log, TEXT("Hello World"));//输出普通语句
        UE_LOG(LogTemp, Warning, TEXT("Hello World"));//输出黄色语句
        UE_LOG(LogTemp, Error, TEXT("Hello World"));//输出红色语句
    }
目标删除自定义的C++类
    工程目录\Source\BasicTraining c++定义类.cpp+.h删除
    工程目录\Binaries 连根删除
    对BasicTraining.uproject 右键第三个选项 Generate Visual Studio project files
    对BasicTraining.uproject 右键第一个选项 open 

新建class在自己设定的路径后 会出现C1083错误
    解决方法将路径下 新建的cpp头文件的路径删除即可
        例#include "Actors/MyActor.h" -> #include "MyActor.h"

.h之中文件内的命名规则
    派生自Actor的类带有A前缀
    派生自Object的类带有U前缀
    Enums的前缀是E
    Interface的前缀是I
    Template的前缀是T
    派生自SWidget的类(Slate UI)带有前缀S
    其他类的前缀为字母F

MyActor.h
    #pragma once
    #include "CoreMinimal.h"
    #include "GameFramework/Actor.h"
    #include "MyActor.generated.h"
    UCLASS()
    class CPP3DP_API AMyActor : public AActor
    {
        GENERATED_BODY()
    public:	
        AMyActor();//默认的构造函数 用于设置属性默认值
    protected:
        virtual void BeginPlay() override;//重写的虚函数 生成时调用的函数
    public:	
        virtual void Tick(float DeltaTime) override;//每帧调用的函数 DeltaTime帧参数
    };

MyActor.cpp
    #include "MyActor.h"
    AMyActor::AMyActor()
    {
        PrimaryActorTick.bCanEverTick = true;//如果是true将每帧调用Tick 如果是false将不调用
    }
    void AMyActor::BeginPlay()
    {
        Super::BeginPlay();//保证能运行
    }
    void AMyActor::Tick(float DeltaTime)
    {
        Super::Tick(DeltaTime);
    }


vs中F12定位源代码 或者右键 速览定义(alt+F12)

staticmesh 静态网格体

end键可以让组件降落到物体的(物理)表面上

在c++中创建静态网格组件
    MyActor.h
        #pragma once
        #include "CoreMinimal.h"
        #include "GameFramework/Actor.h"
        #include "MyActor.generated.h"
        UCLASS()
        class CPP3DP_API AMyActor : public AActor
        {
            GENERATED_BODY()
        public:	
            AMyActor();//默认的构造函数 用于设置属性默认值
            UPROPERTY(VisibleAnywhere,Category="My Actor Components")//可见
            UStaticMeshComponent* StaticMesh;//生成一个指针
        protected:
            virtual void BeginPlay() override;//重写的虚函数 生成时调用的函数
        public:	
            virtual void Tick(float DeltaTime) override;//每帧调用的函数 DeltaTime帧参数
        };

    MyActor.cpp
        #include "MyActor.h"
        AMyActor::AMyActor()
        {
            PrimaryActorTick.bCanEverTick = true;//如果是true将每帧调用Tick 如果是false将不调用

            StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));
        }
        void AMyActor::BeginPlay()
        {
            Super::BeginPlay();//保证能运行
        }
        void AMyActor::Tick(float DeltaTime)
        {
            Super::Tick(DeltaTime);
        }

    随后创建该BP蓝图类则可以看到左上角继承了MyStaticMesh的静态网格组件

增加力 与力矩
    MyActor.h
        #pragma once
        #include "CoreMinimal.h"
        #include "GameFramework/Actor.h"

        #include "MyActor.generated.h"
        UCLASS()
        class CPP3DP_API AMyActor : public AActor
        {
            GENERATED_BODY()
        public:	
            AMyActor();//默认的构造函数 用于设置属性默认值

            UPROPERTY(VisibleAnywhere,Category="My Actor Properties")//可见 再分类
            UStaticMeshComponent* StaticMesh;//生成一个指针 注意:指针类型千万不要设为EditAnywhere

            UPROPERTY(EditInstanceOnly, Category = "My Actor Properties | Vector")//只允许在示例上编辑 再分类
            FVector InitLocation;//初始化位置

            UPROPERTY(VisibleInstanceOnly, Category = "My Actor Properties | Vector")//只允许显示在编辑器上 再分类
            FVector PlacedLocation;//记录初始位置

            UPROPERTY(EditDefaultsOnly, Category = "My Actor Properties | Vector")//只允许在模板上编辑 编辑器上看不到 再分类
            bool bGotoInitLocation;//必须要b开头命名规则

            UPROPERTY(VisibleDefaultsOnly, Category = "My Actor Properties | Vector")//不可被修改 再分类
            FVector WorldOrigin;//参考世界坐标

            UPROPERTY(EditAnywhere, Category = "My Actor Properties | Vector",//可见随处可改 再分类
                meta = (ClampMin = -5.0f, ClampMax = 5.0f, UIMin = -5.0f, UIMax = 5.0f))//限定范围
            FVector TickLocationOffset;//每一帧偏移量

            UPROPERTY(EditAnywhere, Category = "My Actor Properties | Physics")//可见随处可改 再分类
            bool bShouldMove;//必须b开头 必须移动

            UPROPERTY(EditInstanceOnly, Category = "My Actor Properties | Physics")//只允许在示例上编辑 再分类
            FVector InitForce;//初始力

            UPROPERTY(EditInstanceOnly, Category = "My Actor Properties | Physics")//只允许在示例上编辑 再分类
            FVector InitTorque;//初始力矩

            UPROPERTY(EditInstanceOnly, Category = "My Actor Properties | Physics")//只允许在示例上编辑 再分类
            bool bAccelChange;//是否忽略质量

        protected:
            virtual void BeginPlay() override;//重写的虚函数 生成时调用的函数
        public:	
            virtual void Tick(float DeltaTime) override;//每帧调用的函数 DeltaTime帧参数
        };

    MyActor.cpp
    #include "MyActor.h"
    #include "Components/StaticMeshComponent.h"
    AMyActor::AMyActor()
    {
        PrimaryActorTick.bCanEverTick = true;//如果是true将每帧调用Tick 如果是false将不调用

        StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));//创建组件静态网格体

        InitLocation = FVector(0.0f);//初始化位置
        PlacedLocation = FVector(0.0f);//初始化初始位置的存储数据
        bGotoInitLocation = false;//默认不去 在原来位置
        WorldOrigin == FVector(0.0f);//世界坐标参考定义
        TickLocationOffset = FVector(0.0f);//默认每帧偏移量0f
        bShouldMove = false;//非必须移动

        InitForce = FVector(0.0f);
        InitTorque = FVector(0.0f);
        bAccelChange = false;
    }
    void AMyActor::BeginPlay()
    {
        Super::BeginPlay();//保证能运行InitLocation
        PlacedLocation = GetActorLocation();//获取初始位置
        if (bGotoInitLocation)//如果被移动 则跳出转到指定位置
        {
            SetActorLocation(InitLocation);//设置actor位置
                            //传入一个值 让xyz都变成传入值
                            //传入三个值 分别赋值xyz
        }
        //搜索unreal doc 的UStaticMeshComponent指针类型c++ API 第一个 随后寻找到最后的Header
        //找到Runtime/Engine/Classes/Components/StaticMeshComponent.h
        //将Classes后面的复制加到头文件
        StaticMesh->AddForce(InitForce,"NAME_None",bAccelChange);
        StaticMesh->AddTorque(InitTorque, "NAME_None", bAccelChange);
    }
    void AMyActor::Tick(float DeltaTime)
    {
        Super::Tick(DeltaTime);
        if (bShouldMove) {//应该进行移动
            AddActorLocalOffset(TickLocationOffset);//偏移量 每一帧
        }
    }

碰撞
    角色可迈上去
        不碰撞
        仅查询 检验射线是否有物体阻挡 程序内部查询物理的结果
        仅物理 真切碰撞
        启用碰撞
        MyActor.h
            #pragma once
            #include "CoreMinimal.h"
            #include "GameFramework/Actor.h"

            #include "MyActor.generated.h"
            UCLASS()
            class CPP3DP_API AMyActor : public AActor
            {
                GENERATED_BODY()
            public:	
                AMyActor();//默认的构造函数 用于设置属性默认值

                UPROPERTY(VisibleAnywhere,Category="My Actor Properties")//可见 再分类
                UStaticMeshComponent* StaticMesh;//生成一个指针 注意:指针类型千万不要设为EditAnywhere

                UPROPERTY(EditInstanceOnly, Category = "My Actor Properties | Vector")//只允许在示例上编辑 再分类
                FVector InitLocation;//初始化位置

                UPROPERTY(VisibleInstanceOnly, Category = "My Actor Properties | Vector")//只允许显示在编辑器上 再分类
                FVector PlacedLocation;//记录初始位置

                UPROPERTY(EditDefaultsOnly, Category = "My Actor Properties | Vector")//只允许在模板上编辑 编辑器上看不到 再分类
                bool bGotoInitLocation;//必须要b开头命名规则

                UPROPERTY(VisibleDefaultsOnly, Category = "My Actor Properties | Vector")//不可被修改 再分类
                FVector WorldOrigin;//参考世界坐标

                UPROPERTY(EditAnywhere, Category = "My Actor Properties | Vector",//可见随处可改 再分类
                    meta = (ClampMin = -5.0f, ClampMax = 5.0f, UIMin = -5.0f, UIMax = 5.0f))//限定范围
                FVector TickLocationOffset;//每一帧偏移量

                UPROPERTY(EditAnywhere, Category = "My Actor Properties | Physics")//可见随处可改 再分类
                bool bShouldMove;//必须b开头 必须移动

                UPROPERTY(EditInstanceOnly, Category = "My Actor Properties | Physics")//只允许在示例上编辑 再分类
                FVector InitForce;//初始力

                UPROPERTY(EditInstanceOnly, Category = "My Actor Properties | Physics")//只允许在示例上编辑 再分类
                FVector InitTorque;//初始力矩

                UPROPERTY(EditInstanceOnly, Category = "My Actor Properties | Physics")//只允许在示例上编辑 再分类
                bool bAccelChange;//是否忽略质量

            protected:
                virtual void BeginPlay() override;//重写的虚函数 生成时调用的函数
            public:	
                virtual void Tick(float DeltaTime) override;//每帧调用的函数 DeltaTime帧参数
            };

        MyActor.cpp
            #include "MyActor.h"
            #include "Components/StaticMeshComponent.h"
            AMyActor::AMyActor()
            {
                PrimaryActorTick.bCanEverTick = true;//如果是true将每帧调用Tick 如果是false将不调用

                StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));//创建组件静态网格体

                InitLocation = FVector(0.0f);//初始化位置
                PlacedLocation = FVector(0.0f);//初始化初始位置的存储数据
                bGotoInitLocation = false;//默认不去 在原来位置
                WorldOrigin == FVector(0.0f);//世界坐标参考定义
                TickLocationOffset = FVector(0.0f);//默认每帧偏移量0f
                bShouldMove = false;//非必须移动

                InitForce = FVector(0.0f);
                InitTorque = FVector(0.0f);
                bAccelChange = false;
            }
            void AMyActor::BeginPlay()
            {
                Super::BeginPlay();//保证能运行InitLocation
                PlacedLocation = GetActorLocation();//获取初始位置
                if (bGotoInitLocation)//如果被移动 则跳出转到指定位置
                {
                    SetActorLocation(InitLocation);//设置actor位置
                                    //传入一个值 让xyz都变成传入值
                                    //传入三个值 分别赋值xyz
                }
                //搜索unreal doc 的UStaticMeshComponent指针类型c++ API 第一个 随后寻找到最后的Header
                //找到Runtime/Engine/Classes/Components/StaticMeshComponent.h
                //将Classes后面的复制加到头文件
                //StaticMesh->AddForce(InitForce,"NAME_None",bAccelChange);//模拟物理
                //StaticMesh->AddTorque(InitTorque, "NAME_None", bAccelChange);
            }
            void AMyActor::Tick(float DeltaTime)
            {
                Super::Tick(DeltaTime);
                if (bShouldMove) {//应该进行移动
                    FHitResult HitResult;//
                    AddActorLocalOffset(TickLocationOffset,true,&HitResult);//偏移量 每一帧,启用扫描
                    UE_LOG(LogTemp, Warning, TEXT("X:%f , Y:%f , Z:%f"), 
                        HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z);//不断输出接触后 输出击中信息

                }
            }

Pawn类 继承Actor 可以被Actor控制 且可以接收控制台(Controller)输入做出响应
    Tick移动
        MyPawn.cpp
            #include "MyPawn.h"
            #include "Components/StaticMeshComponent.h"//注意要在类名之后添加头文件
            #include "Camera/CameraComponent.h"//Camera相机组件
            #include "Components/InputComponent.h"//键盘映射绑定
            AMyPawn::AMyPawn()//构造函数
            {
                PrimaryActorTick.bCanEverTick = true;

                RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));//创建默认根组件
                MyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));//创建组件静态网格体
                MyStaticMesh->SetupAttachment(GetRootComponent());//组件的附加

                MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));
                MyCamera->SetupAttachment(GetRootComponent());

                MyCamera->SetRelativeLocation(FVector(-300.0f,0.0f,300.0f));//设定摄像头预制坐标
                MyCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));//设定摄像头预制坐标

                AutoPossessPlayer = EAutoReceiveInput::Player0;//设为0号玩家

                MaxSpeed = 100.0f;
                Velocity = FVector::ZeroVector;
            }
            void AMyPawn::BeginPlay()
            {
                Super::BeginPlay();
            }
            void AMyPawn::Tick(float DeltaTime)
            {
                Super::Tick(DeltaTime);
                AddActorLocalOffset(Velocity * DeltaTime, true);
            }
            void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
            {
                Super::SetupPlayerInputComponent(PlayerInputComponent);

                //记得现在设置 引擎 输入中修改映射
                PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyPawn::MoveForward);//按键映射与轴事件绑定 传递函数引用
                PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyPawn::MoveRight);
            }

            void AMyPawn::MoveForward(float Value)
            {
                Velocity.X = FMath::Clamp(Value,-1.0f,1.0f) * MaxSpeed;//控制在-1~1之间
            }

            void AMyPawn::MoveRight(float Value)
            {
                Velocity.Y = FMath::Clamp(Value, -1.0f, 1.0f) * MaxSpeed;//控制在-1~1之间
            }

        MyPawn.h
            #pragma once
            #include "CoreMinimal.h"
            #include "GameFramework/Pawn.h"
            #include "MyPawn.generated.h"
            UCLASS()//APawn已经做完附加 因而可以不用添上
            class CPP3DP_API AMyPawn : public APawn
            {
                GENERATED_BODY()
            public:
                AMyPawn();

                UPROPERTY(VisibleAnywhere, Category = "My Pawn Components")//可见 不可改
                class UStaticMeshComponent* MyStaticMesh;//生成一个指针 注意:指针类型千万不要设为EditAnywhere
                    //添加clss前缀为规避不必要的麻烦

                UPROPERTY(VisibleAnywhere, Category = "My Pawn Components")//可见 不可改
                class UCameraComponent* MyCamera;

                UPROPERTY(EditAnywhere, Category = "My Pawn Movement")//可见 可改
                float MaxSpeed;//最大的速度

            protected:
                virtual void BeginPlay() override;
            public:	
                virtual void Tick(float DeltaTime) override;
                virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
            private:
                void MoveForward(float Value);
                void MoveRight(float Value);
                FVector Velocity;//速度
            };

DeltaTime进行移动可以让物体运动的速度不受帧率影响
TAB上方按键 t.MaxFPS设定最大帧率
SpringArm组件
    MyPawn.h
        #pragma once
        #include "CoreMinimal.h"
        #include "GameFramework/Pawn.h"
        #include "MyPawn.generated.h"
        UCLASS()//APawn已经做完附加 因而可以不用添上
        class CPP3DP_API AMyPawn : public APawn
        {
            GENERATED_BODY()
        public:
            AMyPawn();

            UPROPERTY(VisibleAnywhere, Category = "My Pawn Components")//可见 不可改
            class UStaticMeshComponent* MyStaticMesh;//生成一个指针 注意:指针类型千万不要设为EditAnywhere
                //添加clss前缀为规避不必要的麻烦

            UPROPERTY(VisibleAnywhere, Category = "My Pawn Components")//可见 不可改
            class USpringArmComponent* MySpringArm;

            UPROPERTY(VisibleAnywhere, Category = "My Pawn Components")//可见 不可改
            class UCameraComponent* MyCamera;

            UPROPERTY(EditAnywhere, Category = "My Pawn Movement")//可见 可改
            float MaxSpeed;//最大的速度

        protected:
            virtual void BeginPlay() override;
        public:	
            virtual void Tick(float DeltaTime) override;
            virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
        private:
            void MoveForward(float Value);
            void MoveRight(float Value);
            FVector Velocity;//速度
        };

    MyPawn.cpp
        #include "MyPawn.h"
        #include "Components/StaticMeshComponent.h"//注意要在类名之后添加头文件
        #include "Camera/CameraComponent.h"//Camera相机组件
        #include "Components/InputComponent.h"//键盘映射绑定
        #include "GameFramework/SpringArmComponent.h"//SpringArm头文件
        AMyPawn::AMyPawn()//构造函数
        {
            PrimaryActorTick.bCanEverTick = true;

            RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));//创建默认根组件
            MyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));//创建组件静态网格体
            MyStaticMesh->SetupAttachment(GetRootComponent());//组件的附加

            MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MySpringArm"));
            MySpringArm->SetupAttachment(MyStaticMesh);
            //MySpringArm->RelativeRotation = FRotator(FRotator(-45.0f, 0.0f, 0.0f));//私有无法修改 视频bug
            MySpringArm->TargetArmLength = 400.0f;
            MySpringArm->bEnableCameraLag = true;
            MySpringArm->CameraLagSpeed = 3.0f;


            MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));
            //MyCamera->SetupAttachment(GetRootComponent());
            MyCamera->SetupAttachment(MySpringArm);

            //MyCamera->SetRelativeLocation(FVector(-300.0f,0.0f,300.0f));//设定摄像头预制坐标
            //MyCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));//设定摄像头预制坐标

            AutoPossessPlayer = EAutoReceiveInput::Player0;//设为0号玩家

            MaxSpeed = 100.0f;
            Velocity = FVector::ZeroVector;
        }
        void AMyPawn::BeginPlay()
        {
            Super::BeginPlay();
        }
        void AMyPawn::Tick(float DeltaTime)
        {
            Super::Tick(DeltaTime);
            AddActorLocalOffset(Velocity * DeltaTime, true);
        }
        void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
        {
            Super::SetupPlayerInputComponent(PlayerInputComponent);

            //记得现在设置 引擎 输入中修改映射
            PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyPawn::MoveForward);//按键映射与轴事件绑定 传递函数引用
            PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyPawn::MoveRight);
        }

        void AMyPawn::MoveForward(float Value)
        {
            Velocity.X = FMath::Clamp(Value,-1.0f,1.0f) * MaxSpeed;//控制在-1~1之间
        }

        void AMyPawn::MoveRight(float Value)
        {
            Velocity.Y = FMath::Clamp(Value, -1.0f, 1.0f) * MaxSpeed;//控制在-1~1之间
        }

使用c++代码设置模型与材质的默认值
    MyPawn.h
        #pragma once
        #include "CoreMinimal.h"
        #include "GameFramework/Pawn.h"
        #include "MyPawn.generated.h"
        UCLASS()//APawn已经做完附加 因而可以不用添上
        class CPP3DP_API AMyPawn : public APawn
        {
            GENERATED_BODY()
        public:
            AMyPawn();

            UPROPERTY(VisibleAnywhere, Category = "My Pawn Components")//可见 不可改
            class UStaticMeshComponent* MyStaticMesh;//生成一个指针 注意:指针类型千万不要设为EditAnywhere
                //添加clss前缀为规避不必要的麻烦

            UPROPERTY(VisibleAnywhere, Category = "My Pawn Components")//可见 不可改
            class USpringArmComponent* MySpringArm;

            UPROPERTY(VisibleAnywhere, Category = "My Pawn Components")//可见 不可改
            class UCameraComponent* MyCamera;

            UPROPERTY(EditAnywhere, Category = "My Pawn Movement")//可见 可改
            float MaxSpeed;//最大的速度

            FORCEINLINE UStaticMeshComponent* GetUStaticMeshComponent() { return MyStaticMesh; }
            FORCEINLINE USpringArmComponent* GetUSpringArmComponent() { return MySpringArm; }

        protected:
            virtual void BeginPlay() override;
        public:	
            virtual void Tick(float DeltaTime) override;
            virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
        private:
            void MoveForward(float Value);
            void MoveRight(float Value);
            FVector Velocity;//速度
        };

    MyPawn.cpp
        #include "MyPawn.h"
        #include "Components/StaticMeshComponent.h"//注意要在类名之后添加头文件
        #include "Camera/CameraComponent.h"//Camera相机组件
        #include "Components/InputComponent.h"//键盘映射绑定
        #include "GameFramework/SpringArmComponent.h"//SpringArm头文件
        #include "UObject/ConstructorHelpers.h"//帮助创建东西类 静态类
        AMyPawn::AMyPawn()//构造函数
        {
            PrimaryActorTick.bCanEverTick = true;

            RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));//创建默认根组件
            MyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));//创建组件静态网格体
            MyStaticMesh->SetupAttachment(GetRootComponent());//组件的附加

            static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset=
                (TEXT("Material'/Game/Models/Materials/NewMaterial.NewMaterial'"));//构建静态网格
            //对static mesh对象右键 复制引用 将其路径寻找出(由于本工程内没有 因此用素材代替

            static ConstructorHelpers::FObjectFinder<UMaterialInterface> MateriaAsset =
                (TEXT("Material'/Game/Models/Materials/NewMaterial.NewMaterial'"));
            //材质球
            if (StaticMeshAsset.Succeeded() && MateriaAsset.Succeeded()) {//若创建成功
                //附上模型和材质
                MyStaticMesh->SetStaticMesh(StaticMeshAsset.Object);
                MyStaticMesh->SetMaterial(0, MateriaAsset.Object);
                MyStaticMesh->SetWorldScale3D(FVector(0.5f));//缩小0.5
            }

            MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MySpringArm"));
            //MySpringArm->SetupAttachment(MyStaticMesh);
            MySpringArm->SetupAttachment(GetUStaticMeshComponent());
            //MySpringArm->RelativeRotation = FRotator(FRotator(-45.0f, 0.0f, 0.0f));//私有无法修改 视频bug
            MySpringArm->TargetArmLength = 400.0f;
            MySpringArm->bEnableCameraLag = true;
            MySpringArm->CameraLagSpeed = 3.0f;


            MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));
            //MyCamera->SetupAttachment(GetRootComponent());
            //MyCamera->SetupAttachment(MySpringArm);
            MyCamera->SetupAttachment(GetUSpringArmComponent());

            //MyCamera->SetRelativeLocation(FVector(-300.0f,0.0f,300.0f));//设定摄像头预制坐标
            //MyCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));//设定摄像头预制坐标

            AutoPossessPlayer = EAutoReceiveInput::Player0;//设为0号玩家

            MaxSpeed = 100.0f;
            Velocity = FVector::ZeroVector;
        }
        void AMyPawn::BeginPlay()
        {
            Super::BeginPlay();
        }
        void AMyPawn::Tick(float DeltaTime)
        {
            Super::Tick(DeltaTime);
            AddActorLocalOffset(Velocity * DeltaTime, true);
        }
        void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
        {
            Super::SetupPlayerInputComponent(PlayerInputComponent);

            //记得现在设置 引擎 输入中修改映射
            PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyPawn::MoveForward);//按键映射与轴事件绑定 传递函数引用
            PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyPawn::MoveRight);
        }

        void AMyPawn::MoveForward(float Value)
        {
            Velocity.X = FMath::Clamp(Value,-1.0f,1.0f) * MaxSpeed;//控制在-1~1之间
        }

        void AMyPawn::MoveRight(float Value)
        {
            Velocity.Y = FMath::Clamp(Value, -1.0f, 1.0f) * MaxSpeed;//控制在-1~1之间
        }

Sweep仅对根组件生效
    MyPawn.h的
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));//创建默认根组件
	MyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));//创建组件静态网格体
	MyStaticMesh->SetupAttachment(GetRootComponent());//组件的附加
    改成
	MyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));//创建组件静态网格体
	RootComponent = MyStaticMesh;//成为了根组件 又保留了可编辑的情况
控制视野上下查看 左右旋转
    设置 引擎 输入 映射中设置
    MyPawn.h
        #pragma once
        #include "CoreMinimal.h"
        #include "GameFramework/Pawn.h"
        #include "MyPawn.generated.h"
        UCLASS()//APawn已经做完附加 因而可以不用添上
        class CPP3DP_API AMyPawn : public APawn
        {
            GENERATED_BODY()
        public:
            AMyPawn();

            UPROPERTY(VisibleAnywhere, Category = "My Pawn Components")//可见 不可改
            class UStaticMeshComponent* MyStaticMesh;//生成一个指针 注意:指针类型千万不要设为EditAnywhere
                //添加clss前缀为规避不必要的麻烦

            UPROPERTY(VisibleAnywhere, Category = "My Pawn Components")//可见 不可改
            class USpringArmComponent* MySpringArm;

            UPROPERTY(VisibleAnywhere, Category = "My Pawn Components")//可见 不可改
            class UCameraComponent* MyCamera;

            UPROPERTY(EditAnywhere, Category = "My Pawn Movement")//可见 可改
            float MaxSpeed;//最大的速度

            FORCEINLINE UStaticMeshComponent* GetUStaticMeshComponent() { return MyStaticMesh; }
            FORCEINLINE USpringArmComponent* GetUSpringArmComponent() { return MySpringArm; }

        protected:
            virtual void BeginPlay() override;
        public:	
            virtual void Tick(float DeltaTime) override;
            virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
        private:
            void MoveForward(float Value);
            void MoveRight(float Value);
            FVector Velocity;//速度

            void LookUp(float Value);
            void LookRight(float Value);
            FVector MouseInput;//鼠标速度
        };

    MyPawn.cpp
        #include "MyPawn.h"
        #include "Components/StaticMeshComponent.h"//注意要在类名之后添加头文件
        #include "Camera/CameraComponent.h"//Camera相机组件
        #include "Components/InputComponent.h"//键盘映射绑定
        #include "GameFramework/SpringArmComponent.h"//SpringArm头文件
        #include "UObject/ConstructorHelpers.h"//帮助创建东西类 静态类
        AMyPawn::AMyPawn()//构造函数
        {
            PrimaryActorTick.bCanEverTick = true;

            //RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));//创建默认根组件
            MyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));//创建组件静态网格体
            RootComponent = MyStaticMesh;//成为了根组件 又保留了可编辑的情况
            //MyStaticMesh->SetupAttachment(GetRootComponent());//组件的附加

            //RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));//用于测试

            static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset=
                (TEXT("Material'/Game/Models/Materials/NewMaterial.NewMaterial'"));//构建静态网格
            //对static mesh对象右键 复制引用 将其路径寻找出(由于本工程内没有 因此用素材代替

            static ConstructorHelpers::FObjectFinder<UMaterialInterface> MateriaAsset =
                (TEXT("Material'/Game/Models/Materials/NewMaterial.NewMaterial'"));
            //材质球
            if (StaticMeshAsset.Succeeded() && MateriaAsset.Succeeded()) {//若创建成功
                //附上模型和材质
                MyStaticMesh->SetStaticMesh(StaticMeshAsset.Object);
                MyStaticMesh->SetMaterial(0, MateriaAsset.Object);
                MyStaticMesh->SetWorldScale3D(FVector(0.5f));//缩小0.5
            }

            MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MySpringArm"));
            //MySpringArm->SetupAttachment(MyStaticMesh);
            MySpringArm->SetupAttachment(GetUStaticMeshComponent());
            //MySpringArm->RelativeRotation = FRotator(FRotator(-45.0f, 0.0f, 0.0f));//私有无法修改 视频bug
            MySpringArm->TargetArmLength = 400.0f;
            MySpringArm->bEnableCameraLag = true;
            MySpringArm->CameraLagSpeed = 3.0f;


            MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));
            //MyCamera->SetupAttachment(GetRootComponent());
            //MyCamera->SetupAttachment(MySpringArm);
            MyCamera->SetupAttachment(GetUSpringArmComponent());

            //MyCamera->SetRelativeLocation(FVector(-300.0f,0.0f,300.0f));//设定摄像头预制坐标
            //MyCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));//设定摄像头预制坐标

            AutoPossessPlayer = EAutoReceiveInput::Player0;//设为0号玩家
            bUseControllerRotationYaw = true;//开启选项
            MaxSpeed = 100.0f;
            Velocity = FVector::ZeroVector;
        }
        void AMyPawn::BeginPlay()
        {
            Super::BeginPlay();
        }
        void AMyPawn::Tick(float DeltaTime)
        {
            Super::Tick(DeltaTime);
            AddActorLocalOffset(Velocity * DeltaTime, true);//限制

            //鼠标上下旋转操作
            FRotator NewSpringArmRotation = MySpringArm->GetComponentRotation();//限制
            //x,y,z -> row ,pitch ,yaw
            NewSpringArmRotation.Pitch = FMath::Clamp(NewSpringArmRotation.Pitch += MouseInput.Y, -80.0f, 0.0f);//累加
            MySpringArm->SetWorldRotation(NewSpringArmRotation);//修改rotation

            //鼠标左右旋转 要记得controller的继承
            AddControllerYawInput(MouseInput.X);//bUseControllerRotationYaw = true;//开启选项
        }
        void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
        {
            Super::SetupPlayerInputComponent(PlayerInputComponent);

            //记得现在设置 引擎 输入中修改映射
            PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyPawn::MoveForward);//按键映射与轴事件绑定 传递函数引用
            PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyPawn::MoveRight);
            PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMyPawn::LookUp);
            PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AMyPawn::LookRight);
        }

        void AMyPawn::MoveForward(float Value)
        {
            Velocity.X = FMath::Clamp(Value,-1.0f,1.0f) * MaxSpeed;//控制在-1~1之间
        }

        void AMyPawn::MoveRight(float Value)
        {
            Velocity.Y = FMath::Clamp(Value, -1.0f, 1.0f) * MaxSpeed;//控制在-1~1之间
        }

        void AMyPawn::LookUp(float Value)
        {
            MouseInput.Y = FMath::Clamp(Value, -1.0f, 1.0f);//控制在-1~1之间
        }

        void AMyPawn::LookRight(float Value)
        {
            MouseInput.X = FMath::Clamp(Value, -1.0f, 1.0f);//控制在-1~1之间
        }

