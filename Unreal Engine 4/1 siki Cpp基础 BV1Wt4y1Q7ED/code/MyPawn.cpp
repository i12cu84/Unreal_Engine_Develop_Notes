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

