#include "BP_SaveConstraintToFile.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#include "Math/Vector.h"
#include "Components/LineBatchComponent.h"
#include <fstream>
#include <string>
#include <vector>
#include "Misc/Paths.h"

#include "Engine/Texture2D.h"
#include "Engine/Texture2DDynamic.h"
#include "Modules/ModuleManager.h"

#include "../../Runtime/ImageWrapper/Public/IImageWrapperModule.h"

bool UBP_SaveConstraintToFile::SaveConstraintArray(FString SaveDirectory, FString Filename, TArray<FString> SaveText, bool AllowOverWriting=false)
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

	return FFileHelper::SaveStringToFile(FinalString, *SaveDirectory,FFileHelper::EEncodingOptions::ForceUTF8);
	return false;
}

TArray<FString> UBP_SaveConstraintToFile::LoadConstraintArray(FString FilePath)
{
	TArray<FString> OutData;
    std::string FilePathStr(TCHAR_TO_UTF8(*FilePath));
    std::ifstream File(FilePathStr);
    if (!File.is_open())
    {
        return OutData;
    }
    std::string Line;
    while (std::getline(File, Line))
    {
        OutData.Add(FString(Line.c_str()));
    }
    File.close();
	return OutData;
}

bool UBP_SaveConstraintToFile::DeleteFile(FString FilePath)
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

TArray < ULineBatchComponent* > UBP_SaveConstraintToFile::DrawRayLine(FVector StartPos, FVector EndPos, float fLifeTime, FLinearColor color)
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

void UBP_SaveConstraintToFile::DestoryLine(TArray <ULineBatchComponent*> LineList)
{
	for (int i = 0; i < LineList.Num(); i++)
	{
		LineList[i]->Flush();
	}

}

TArray<FString> UBP_SaveConstraintToFile::GetAllSaveFileNames(const FString& Directory)
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

FString UBP_SaveConstraintToFile::GetFileNameFromPath(const FString& FilePath)
{
	FString FileNameWithoutExtension = FPaths::GetBaseFilename(FilePath);

	return FileNameWithoutExtension;
}

UTexture2D* UBP_SaveConstraintToFile::LoadImageByAbsolutePath(const FString& AbsolutePath)
{
	UObjectLibrary* ObjectLibrary = UObjectLibrary::CreateLibrary(UTexture2D::StaticClass(), false, true);
	ObjectLibrary->AddToRoot();
	ObjectLibrary->LoadAssetDataFromPath(AbsolutePath);

	TArray<FAssetData> AssetData;
	ObjectLibrary->GetAssetDataList(AssetData);

	ObjectLibrary->RemoveFromRoot();
	ObjectLibrary->ClearLoaded();

	if (AssetData.Num() > 0)
	{
		UTexture2D* LoadedTexture = Cast<UTexture2D>(AssetData[0].GetAsset());
		return LoadedTexture;
	}
	else
	{
		return nullptr;
	}
}

UTexture2D* UBP_SaveConstraintToFile::LoadImageFromAbsolutePath(const FString& AbsolutePath)
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

UMediaSource* UBP_SaveConstraintToFile::LoadMediaSourceFromAbsolutePath(const FString& AbsolutePath)
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
