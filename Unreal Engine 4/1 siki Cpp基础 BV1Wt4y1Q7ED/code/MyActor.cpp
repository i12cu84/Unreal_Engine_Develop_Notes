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
		FHitResult HitResult;//射线用于检测
		AddActorLocalOffset(TickLocationOffset* DeltaTime,true,&HitResult);//偏移量 每一帧,启用扫描
											//乘上DeltaTime即可不会被帧率所影响
		UE_LOG(LogTemp, Warning, TEXT("X:%f , Y:%f , Z:%f"), 
			HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z);//不断输出接触后 输出击中信息

	}
}

