
#pragma once

#include "../../../CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "../../../CoreUObject/Public/UObject/UObjectGlobals.h"
#include "Engine/ObjectLibrary.h"

#include "../../Runtime/SlateCore/Public/Brushes/SlateImageBrush.h"
#include "../../Runtime/ImageWrapper/Public/IImageWrapperModule.h"
#include "../../Runtime/ImageWrapper/Public/IImageWrapper.h"

#include "Misc/FileHelper.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BP_SaveConstraintToFile.generated.h"
/**
 * 
 */
UCLASS()
class REPAIR_API UBP_SaveConstraintToFile : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	//����浵
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Save"))
		static bool SaveConstraintArray(FString SaveDirectory, FString Filename, TArray<FString>SaveText, bool AllowOverWriting);

	//���ش浵
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Load"))
		static TArray<FString> LoadConstraintArray(FString FilePath);
	
	//ɾ���浵
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Delete"))
		static bool DeleteFile(FString FilePath);

	//����
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Draw"))
		static TArray<ULineBatchComponent*> DrawRayLine(FVector StartPos, FVector EndPos, float fLifeTime, FLinearColor color);

	//ɾ��
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Destroy"))
		static void DestoryLine(TArray<ULineBatchComponent*> LineList);

	//��ȡ·���µĴ浵������
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "SavedFileName"))
		static TArray<FString> GetAllSaveFileNames(const FString& Directory);

	//��ȡ·���ļ�����
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "ExtraceSavedFileName"))
		static FString GetFileNameFromPath(const FString & FilePath);

	//��ȡ·��ͼƬ
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Image"))
		static UTexture2D* LoadImageByAbsolutePath(const FString& AbsolutePath);

	//��ȡͼƬ
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Image"))
		static UTexture2D* LoadImageFromAbsolutePath(const FString& AbsolutePath);
	
	//��ȡ��Ƶ����
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "media"))
		static UMediaSource* LoadMediaSourceFromAbsolutePath(const FString& AbsolutePath);
	

};