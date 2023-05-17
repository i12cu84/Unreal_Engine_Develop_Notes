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
