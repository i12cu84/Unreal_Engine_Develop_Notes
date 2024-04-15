// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// MSVC
#include <fstream>
#include <string>
#include <vector>

//"Engine"
#include "Components/LineBatchComponent.h"
#include "Engine/Texture2D.h"
#include "Engine/Texture2DDynamic.h"
#include "Kismet/BlueprintFunctionLibrary.h"

//"Core"
#include "CoreMinimal.h"
#include "HAL/FileManagerGeneric.h"
#include "HAL/PlatformFilemanager.h"
#include "Internationalization/Text.h"
#include "Math/Vector.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Modules/ModuleManager.h"

//"ImageWrapper"
#include "IImageWrapperModule.h"

//"MediaAssets"
#include "MediaAssets/Public/FileMediaSource.h"

#include "FileOperationsBPLibrary.generated.h"

/*
 *	Function library class.
 *	Each function in it is expected to be static and represents blueprint
 *node that can be called in any blueprint.
 *
 *	When declaring function you can define metadata for the node. Key
 *function specifiers will be BlueprintPure and BlueprintCallable. BlueprintPure
 *- means the function does not affect the owning object in any way and thus
 *creates a node without Exec pins. BlueprintCallable - makes a function which
 *can be executed in Blueprints - Thus it has Exec pins. DisplayName - full name
 *of the node, shown when you mouse over the node and in the blueprint drop down
 *menu. Its lets you name the node using characters not allowed in C++ function
 *names. CompactNodeTitle - the word(s) that appear on the node. Keywords -
 *the list of keywords that helps you to find node when you search for it using
 *Blueprint drop-down menu. Good example is "Print String" node which you can
 *find also by using keyword "log". Category -	the category your node will be
 *under in the Blueprint drop-down menu.
 *
 *	For more info on custom blueprint nodes visit documentation:
 *	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
 */
UCLASS()
class UFileOperationsBPLibrary : public UBlueprintFunctionLibrary {
    GENERATED_UCLASS_BODY()

    UFUNCTION(BlueprintCallable,
        meta = (DisplayName = "Execute Sample function",
            Keywords = "FileOperations sample test testing"),
        Category = "FileOperationsTesting")
    static float FileOperationsSampleFunction(float Param);

    // ��ȡ�ļ�
    UFUNCTION(BlueprintCallable, Category = "FileHandle")
    static FString ReadStringToFile(FString Dir) {
        FString Result;
        FFileHelper::LoadFileToString(Result, *Dir);
        return Result;
    }

    // д���ļ� ���ַ� UTF-16
    UFUNCTION(BlueprintCallable, Category = "FileHandle")
    static void WriteStringToFile(FString FileName, FString content) {
        FFileHelper::SaveStringToFile(content, *FileName);
    }

    // д���ļ� UTF-8
    UFUNCTION(BlueprintCallable, Category = "FileHandle")
    static bool WriteStringToFileU8(FString FileName, FString content) {
        return FFileHelper::SaveStringToFile(
            content, *FileName, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
    }

    // Ѱ���ļ�
    UFUNCTION(BlueprintCallable, Category = "File operation")
    static TArray<FString> FindFilesTo(FString Path, FString Filter, bool Files,
        bool Directory) {
        TArray<FString> FilePathList;
        FilePathList.Empty();
        FFileManagerGeneric::Get().FindFilesRecursive(FilePathList, *Path, *Filter,
            Files, Directory);
        return FilePathList;
    }

    // �ƶ��ļ�
    UFUNCTION(BlueprintCallable, Category = "FileHandle")
    static bool MoveFileTo(FString To, FString From) {
        return IFileManager::Get().Move(*To, *From);
    }

    // �����ļ�
    UFUNCTION(BlueprintCallable, Category = "FileHandle")
    static int32 CopyFileTo(FString To, FString From) {
        return IFileManager::Get().Copy(*To, *From);
    }

    // ɾ���ļ�
    UFUNCTION(BlueprintCallable, Category = "FileHandle")
    static bool DeleteFileTo(FString FilePath) {
        return IFileManager::Get().Delete(*FilePath);
    }

    // ���ļ�
    UFUNCTION(BlueprintCallable, Category = "FileHandle")
    static void OpenFile(FString FilePath) {
        FPlatformProcess::CreateProc(*FilePath, nullptr, true, false, false,
            nullptr, 0, nullptr, nullptr);
    }

    // �����ļ���
    UFUNCTION(BlueprintCallable, Category = "FileHandle")
    static void CreateDic(FString filePath) {
        IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
        PlatformFile.CreateDirectory(*filePath);
    }

    // ɾ���ļ���
    UFUNCTION(BlueprintCallable, Category = "FileHandle")
    static void DeleteDic(FString filePath) {
        IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
        PlatformFile.DeleteDirectory(*filePath);
    }

    // ��ȡ�ļ���С
    UFUNCTION(BlueprintCallable, Category = "FileHandle")
    static int64 GitFileSize(FString filePath) {
        IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
        return PlatformFile.FileSize(*filePath);
    }

    // �����ļ�Ŀ¼�µ������ļ�
    UFUNCTION(BlueprintCallable, DisplayName = "FindFolder",
        Category = "FileHandle")
    static TArray<FString> FindFolder(FString Path, FString Filter, bool Files,
        bool Directory) {
        TArray<FString> FilePathList;
        FilePathList.Empty();
        FFileManagerGeneric::Get().FindFilesRecursive(FilePathList, *Path, *Filter,
            Files, Directory);
        return FilePathList;
    }

    // �����ļ�Ŀ¼�������ļ��޷�ɾѡ����
    UFUNCTION(BlueprintCallable, DisplayName = "GetFolderFiles",
        Category = "FileHandle")
    static TArray<FString> GetFolderFiles(FString Path) {
        TArray<FString> Files;
        FPaths::NormalizeDirectoryName(Path);
        IFileManager& FileManager = IFileManager::Get();
        FString FinalPath = Path / TEXT("*");
        FileManager.FindFiles(Files, *FinalPath, true, true);
        return Files;
    }

    // ����
    UFUNCTION(BlueprintCallable, Category = "")
    static void CopyMessageToClipboard(FString text) {
        FPlatformMisc::ClipboardCopy(*text);
    }

    // ճ��
    UFUNCTION(BlueprintCallable, Category = "")
    static FString PasteMessageFromClipboard() {
        FString ClipboardContent;
        FPlatformMisc::ClipboardPaste(ClipboardContent);
        return ClipboardContent;
    }

    // ·���Ƿ���Ч
    UFUNCTION(BlueprintCallable, Category = "")
    static bool IsValidFilePath(const FString& FilePath) {
        // ����ʹ�� FileExists ������ļ�·���Ƿ���Ч
        if (IFileManager::Get().FileExists(*FilePath)) {
            return true;
        }
        return false;
    }

    // ��ȡָ��·�����ļ� ֻ�ܻ�ȡ�ļ���
    UFUNCTION(BlueprintCallable, Category = "")
    static TArray<FString> GetFilesInDirectory(const FString& DirectoryPath) {
        TArray<FString> Files;

        if (FPaths::DirectoryExists(DirectoryPath)) {
            FString SearchPath = FPaths::Combine(DirectoryPath, TEXT("*"));
            TArray<FString> FoundFiles;
            IFileManager::Get().FindFiles(FoundFiles, *SearchPath, false, true);

            for (const FString& FoundFile : FoundFiles) {
                Files.Add(FPaths::Combine(DirectoryPath, FoundFile));
            }
        }

        return Files;
    }

    // ��ȡָ��·�����ļ� ֻ�ܻ�ȡmp3�ļ�
    UFUNCTION(BlueprintCallable, Category = "")
    static TArray<FString> GetMP3FilePaths(const FString& Directory) {
        TArray<FString> MP3FilePaths;

        // ��ȡָ��Ŀ¼�µ������ļ�
        TArray<FString> Files;
        IFileManager::Get().FindFilesRecursive(Files, *Directory, TEXT("*.mp3"),
            true, false);

        // ���ļ�·����ӵ�������
        for (const FString& FilePath : Files) {
            MP3FilePaths.Add(FPaths::ConvertRelativePathToFull(FilePath));
        }

        return MP3FilePaths;
    }

    // ���ļ�·������ȡ�ļ���
    UFUNCTION(BlueprintCallable, Category = "")
    static FString GetFileNameFromPath(const FString& FilePath) {
        FString FileName = FPaths::GetBaseFilename(FilePath);
        return FileName;
    }

    // ɾ���ļ�
    UFUNCTION(BlueprintCallable, Category = "")
    static bool DeleteFileAtPath(const FString& FilePath) {
        // ����ļ�·���Ƿ����
        if (IFileManager::Get().FileExists(*FilePath)) {
            // ����ɾ���ļ�
            if (IFileManager::Get().Delete(*FilePath)) {
                return true; // ɾ���ɹ�
            }
        }
        return false; // ɾ��ʧ��
    }

    // �ɺ�̨����
    UFUNCTION(BlueprintCallable, Category = "")
    static float SetSUVM() {
        FApp::SetUnfocusedVolumeMultiplier(1.0f);
        return FApp::GetUnfocusedVolumeMultiplier();
    }

    // ����浵
    UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Save"))
    static bool SaveConstraintArray(FString SaveDirectory, FString Filename,
        TArray<FString> SaveText,
        bool AllowOverWriting = false) {
        SaveDirectory += "\\";
        SaveDirectory += Filename;

        if (!AllowOverWriting) {
            if (FPlatformFileManager::Get().GetPlatformFile().FileExists(
                *SaveDirectory)) {
                return false;
            }
        }

        FString FinalString = "";
        for (FString& Each : SaveText) {
            FinalString += Each;
            FinalString += LINE_TERMINATOR;
        }

        return FFileHelper::SaveStringToFile(
            FinalString, *SaveDirectory, FFileHelper::EEncodingOptions::ForceUTF8);
        return false;
    }

    // ���ش浵
    UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Load"))
    static TArray<FString> LoadConstraintArray(FString FilePath) {
        TArray<FString> OutData;

        std::string FilePathStr(TCHAR_TO_UTF8(*FilePath));

        FString FileContent;
        if (FFileHelper::LoadFileToString(FileContent, *FilePath)) {
            TArray<FString> Lines;
            FileContent.ParseIntoArrayLines(Lines, false);
            OutData.Append(Lines);
        }

        return OutData;
    }

    // ɾ���浵
    UFUNCTION(BlueprintCallable, Category = "Custom",
        meta = (Keywords = "Delete"))
    static bool DeleteFile(FString FilePath) {
        IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
        if (PlatformFile.DeleteFile(*FilePath)) {
            return true;
        }
        else {
            return false;
        }
    }

    // ����
    UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Draw"))
    static TArray<ULineBatchComponent*> DrawRayLine(FVector StartPos,
        FVector EndPos,
        float fLifeTime,
        FLinearColor color) {
        TArray<ULineBatchComponent*> LineColection;

        ULineBatchComponent* LineBatcher =
            GWorld->GetWorld()->PersistentLineBatcher;
        const float LifeTime = fLifeTime;
        if (LineBatcher != NULL) {
            float LineLifeTime =
                (LifeTime > 0.f) ? LifeTime : LineBatcher->DefaultLifeTime;

            LineBatcher->DrawLine(StartPos, EndPos, color, 10, 2.0f, LineLifeTime);

            LineColection.Add(LineBatcher);
        }
        return LineColection;
    }

    // ɾ��
    UFUNCTION(BlueprintCallable, Category = "Custom",
        meta = (Keywords = "Destroy"))
    static void DestoryLine(TArray<ULineBatchComponent*> LineList) {
        for (int i = 0; i < LineList.Num(); i++) {
            LineList[i]->Flush();
        }
    }

    // ��ȡ·���µĴ浵������
    UFUNCTION(BlueprintCallable, Category = "Custom",
        meta = (Keywords = "SavedFileName"))
    static TArray<FString> GetAllSaveFileNames(const FString& Directory) {
        TArray<FString> OutFileNames;
        IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
        TArray<FString> FoundFiles;
        PlatformFile.FindFilesRecursively(FoundFiles, *Directory, nullptr);
        for (const FString& FoundFile : FoundFiles) {
            if (PlatformFile.FileExists(*FoundFile)) {
                OutFileNames.Add(FoundFile);
            }
        }
        return OutFileNames;
    }

    // ��ȡ·���ļ�����
    UFUNCTION(BlueprintCallable, Category = "Custom",
        meta = (Keywords = "ExtraceSavedFileName"))
    static FString GetFileNamePath(const FString& FilePath) {
        FString FileNameWithoutExtension = FPaths::GetBaseFilename(FilePath);

        return FileNameWithoutExtension;
    }

    // ��ȡͼƬ
    UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Image"))
    static UTexture2D* LoadImageFromAbsolutePath(const FString& AbsolutePath) {
        TArray<uint8> ImageData;
        if (!FFileHelper::LoadFileToArray(ImageData, *AbsolutePath)) {
            return nullptr;
        }

        IImageWrapperModule& ImageWrapperModule =
            FModuleManager::LoadModuleChecked<IImageWrapperModule>(
                FName("ImageWrapper"));
        EImageFormat ImageFormat = ImageWrapperModule.DetectImageFormat(
            ImageData.GetData(), ImageData.Num());

        TSharedPtr<IImageWrapper> ImageWrapper =
            ImageWrapperModule.CreateImageWrapper(ImageFormat);
        if (!ImageWrapper.IsValid() ||
            !ImageWrapper->SetCompressed(ImageData.GetData(), ImageData.Num())) {
            return nullptr;
        }

        TArray<uint8> UncompressedImageData;
        if (!ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedImageData)) {
            return nullptr;
        }

        UTexture2D* Texture = UTexture2D::CreateTransient(
            ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);
        if (!Texture) {
            return nullptr;
        }

        void* TextureData =
            Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
        FMemory::Memcpy(TextureData, UncompressedImageData.GetData(),
            UncompressedImageData.Num());
        Texture->PlatformData->Mips[0].BulkData.Unlock();
        Texture->UpdateResource();

        return Texture;
    }

    // ����UAID��ȡActor
    UFUNCTION(BlueprintCallable, Category = "Custom",
        meta = (Keywords = "GetActor"))
    static AActor* GetActorByName(TArray<AActor*> Actors,
        const FString& ActorName) {
        FString Text = ActorName;
        for (AActor* Actor : Actors) {
            if (Actor && Actor->GetName() == ActorName) {
                UE_LOG(LogTemp, Warning, TEXT("over: %s"), *Text);
                return Actor;
            }
        }
        UE_LOG(LogTemp, Warning, TEXT("missing: %s"), *Text);
        return nullptr;
    }

    // ��ȡ��Ƶ����
    UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "media"))
    static UMediaSource*
        LoadMediaSourceFromAbsolutePath(const FString& AbsolutePath) {
        TArray<uint8> MediaData;
        if (!FFileHelper::LoadFileToArray(MediaData, *AbsolutePath)) {
            return nullptr;
        }

        UMediaSource* MediaSource =
            NewObject<UFileMediaSource>(UFileMediaSource::StaticClass());
        if (!MediaSource) {
            return nullptr;
        }

        UFileMediaSource* FileMediaSource = Cast<UFileMediaSource>(MediaSource);
        if (!FileMediaSource) {
            return nullptr;
        }

        FileMediaSource->FilePath = AbsolutePath;

        return MediaSource;
    }
};
