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
