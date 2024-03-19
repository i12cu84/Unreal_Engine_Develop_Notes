// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "MediaAssets/Public/FileMediaSource.h"
#include "HAL/PlatformFilemanager.h"
#include "Math/Vector.h"
#include "Components/LineBatchComponent.h"
#include "Modules/ModuleManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Engine/Texture2D.h"
#include "Engine/Texture2DDynamic.h"
#include "ImageWrapper\Public\IImageWrapperModule.h"

#include "MyTextBlueprintFunctionLibrary.generated.h"
/**
 *
 */
UCLASS()
class UPLAYER_API UMyTextBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	//复制
	UFUNCTION(BlueprintCallable, Category = "")
	static void CopyMessageToClipboard(FString text)
	{
		FPlatformMisc::ClipboardCopy(*text);
	}

	//粘贴
	UFUNCTION(BlueprintCallable, Category = "")
	static FString PasteMessageFromClipboard()
	{
		FString ClipboardContent;
		FPlatformMisc::ClipboardPaste(ClipboardContent);
		return ClipboardContent;
	}

	//路径是否有效
	UFUNCTION(BlueprintCallable, Category = "")
	static bool IsValidFilePath(const FString& FilePath)
	{
		// 尝试使用 FileExists 来检查文件路径是否有效
		if (IFileManager::Get().FileExists(*FilePath))
		{
			return true;
		}
		return false;
	}

	//获取指定路径的文件 只能获取文件夹
	UFUNCTION(BlueprintCallable, Category = "")
	static TArray<FString> GetFilesInDirectory(const FString& DirectoryPath)
	{
		TArray<FString> Files;

		if (FPaths::DirectoryExists(DirectoryPath))
		{
			FString SearchPath = FPaths::Combine(DirectoryPath, TEXT("*"));
			TArray<FString> FoundFiles;
			IFileManager::Get().FindFiles(FoundFiles, *SearchPath, false, true);

			for (const FString& FoundFile : FoundFiles)
			{
				Files.Add(FPaths::Combine(DirectoryPath, FoundFile));
			}
		}

		return Files;
	}

	//获取指定路径的文件 只能获取mp3文件
	UFUNCTION(BlueprintCallable, Category = "")
	static TArray<FString> GetMP3FilePaths(const FString& Directory)
	{
		TArray<FString> MP3FilePaths;

		// 获取指定目录下的所有文件
		TArray<FString> Files;
		IFileManager::Get().FindFilesRecursive(Files, *Directory, TEXT("*.mp3"), true, false);

		// 将文件路径添加到数组中
		for (const FString& FilePath : Files)
		{
			MP3FilePaths.Add(FPaths::ConvertRelativePathToFull(FilePath));
		}

		return MP3FilePaths;
	}

	//从文件路径中提取文件名
	UFUNCTION(BlueprintCallable, Category = "")
	static FString GetFileNameFromPath(const FString& FilePath)
	{
		FString FileName = FPaths::GetBaseFilename(FilePath);
		return FileName;
	}

	//删除文件
	UFUNCTION(BlueprintCallable, Category = "")
	static bool DeleteFileAtPath(const FString& FilePath)
	{
		// 检查文件路径是否存在
		if (IFileManager::Get().FileExists(*FilePath))
		{
			// 尝试删除文件
			if (IFileManager::Get().Delete(*FilePath))
			{
				return true; // 删除成功
			}
		}
		return false; // 删除失败
	}

	//可后台播放
	UFUNCTION(BlueprintCallable, Category = "")
	static float SetSUVM()
	{
		FApp::SetUnfocusedVolumeMultiplier(1.0f);
		return FApp::GetUnfocusedVolumeMultiplier();
	}

	//保存存档
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Save"))
	static bool SaveConstraintArray(FString SaveDirectory, FString Filename, TArray<FString> SaveText, bool AllowOverWriting = false)
	{
		SaveDirectory += "\\";
		SaveDirectory += Filename;

		if (!AllowOverWriting)
		{
			if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*SaveDirectory))
			{
				return false;
			}
		}

		FString FinalString = "";
		for (FString& Each : SaveText)
		{
			FinalString += Each;
			FinalString += LINE_TERMINATOR;
		}

		return FFileHelper::SaveStringToFile(FinalString, *SaveDirectory, FFileHelper::EEncodingOptions::ForceUTF8);
		return false;
	}

	//加载存档
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Load"))
	static TArray<FString> LoadConstraintArray(FString FilePath)
	{
		TArray<FString> OutData;

		std::string FilePathStr(TCHAR_TO_UTF8(*FilePath));

		FString FileContent;
		if (FFileHelper::LoadFileToString(FileContent, *FilePath))
		{
			TArray<FString> Lines;
			FileContent.ParseIntoArrayLines(Lines, false);
			OutData.Append(Lines);
		}

		return OutData;
	}

	//删除存档
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Delete"))
	static bool DeleteFile(FString FilePath)
	{
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
		if (PlatformFile.DeleteFile(*FilePath))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//画线
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Draw"))
	static TArray<ULineBatchComponent*> DrawRayLine(FVector StartPos, FVector EndPos, float fLifeTime, FLinearColor color)
	{
		TArray < ULineBatchComponent* > LineColection;

		ULineBatchComponent* LineBatcher = GWorld->GetWorld()->PersistentLineBatcher;
		const float LifeTime = fLifeTime;
		if (LineBatcher != NULL)
		{
			float LineLifeTime = (LifeTime > 0.f) ? LifeTime : LineBatcher->DefaultLifeTime;


			LineBatcher->DrawLine(StartPos, EndPos, color, 10, 2.0f, LineLifeTime);

			LineColection.Add(LineBatcher);

		}
		return LineColection;
	}

	//删线
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Destroy"))
	static void DestoryLine(TArray <ULineBatchComponent*> LineList)
	{
		for (int i = 0; i < LineList.Num(); i++)
		{
			LineList[i]->Flush();
		}

	}

	//获取路径下的存档名字组
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "SavedFileName"))
	static TArray<FString> GetAllSaveFileNames(const FString& Directory)
	{
		TArray<FString> OutFileNames;
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
		TArray<FString> FoundFiles;
		PlatformFile.FindFilesRecursively(FoundFiles, *Directory, nullptr);
		for (const FString& FoundFile : FoundFiles)
		{
			if (PlatformFile.FileExists(*FoundFile))
			{
				OutFileNames.Add(FoundFile);
			}
		}
		return OutFileNames;
	}

	//提取路径文件名字
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "ExtraceSavedFileName"))
	static FString GetFileNamePath(const FString& FilePath)
	{
		FString FileNameWithoutExtension = FPaths::GetBaseFilename(FilePath);

		return FileNameWithoutExtension;
	}

	//提取图片
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Image"))
	static UTexture2D* LoadImageFromAbsolutePath(const FString& AbsolutePath)
	{
		TArray<uint8> ImageData;
		if (!FFileHelper::LoadFileToArray(ImageData, *AbsolutePath))
		{
			return nullptr;
		}

		IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
		EImageFormat ImageFormat = ImageWrapperModule.DetectImageFormat(ImageData.GetData(), ImageData.Num());

		TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(ImageFormat);
		if (!ImageWrapper.IsValid() || !ImageWrapper->SetCompressed(ImageData.GetData(), ImageData.Num()))
		{
			return nullptr;
		}

		TArray<uint8> UncompressedImageData;
		if (!ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedImageData))
		{
			return nullptr;
		}

		UTexture2D* Texture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);
		if (!Texture)
		{
			return nullptr;
		}

		void* TextureData = Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
		FMemory::Memcpy(TextureData, UncompressedImageData.GetData(), UncompressedImageData.Num());
		Texture->PlatformData->Mips[0].BulkData.Unlock();
		Texture->UpdateResource();

		return Texture;
	}

	//按照UAID提取Actor
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "GetActor"))
	static AActor* GetActorByName(TArray<AActor*> Actors, const FString& ActorName)
	{
		FString Text = ActorName;
		for (AActor* Actor : Actors)
		{
			if (Actor && Actor->GetName() == ActorName)
			{
				UE_LOG(LogTemp, Warning, TEXT("over: %s"), *Text);
				return Actor;
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("missing: %s"), *Text);
		return nullptr;
	}
	
	//提取视频纹理
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "media"))
	static UMediaSource* LoadMediaSourceFromAbsolutePath(const FString& AbsolutePath)
	{
		TArray<uint8> MediaData;
		if (!FFileHelper::LoadFileToArray(MediaData, *AbsolutePath))
		{
			return nullptr;
		}

		UMediaSource* MediaSource = NewObject<UFileMediaSource>(UFileMediaSource::StaticClass());
		if (!MediaSource)
		{
			return nullptr;
		}

		UFileMediaSource* FileMediaSource = Cast<UFileMediaSource>(MediaSource);
		if (!FileMediaSource)
		{
			return nullptr;
		}

		FileMediaSource->FilePath = AbsolutePath;

		return MediaSource;
	}

};


