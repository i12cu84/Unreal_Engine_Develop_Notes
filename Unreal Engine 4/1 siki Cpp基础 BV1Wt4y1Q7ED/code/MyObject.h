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
