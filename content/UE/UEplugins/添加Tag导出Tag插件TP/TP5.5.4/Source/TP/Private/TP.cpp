// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP.h"
#include "TPStyle.h"
#include "TPCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "EditorWorldExtension.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
//#include "../LevelEditor/Public/LevelEditorActions.h"
//#include "Framework/Commands/LevelEditorActions.h"
#include "../../../Source/Editor/LevelEditor/Public/LevelEditorActions.h"
#include "../../../Source/Editor/UnrealEd/Public/Editor.h"
#include "CoreMinimal.h"
//#include "../../Core/Public/CoreMinimal.h"
#include "../../Core/Public/Misc/Paths.h"
#include "../../Core/Public/Misc/DateTime.h"

#include <string>
#include <cstring>
#include <iostream>
#include <cwchar>
#include <cstdlib>
#include <locale>
#include <codecvt>
#include <set>
#include <omp.h>
#include <chrono>

#include "../../../Slate/Public/SlateBasics.h"
#include "../../../../SlateCore/Public/Widgets/SCompoundWidget.h"
#include "../../../../Slate/Public/Widgets/Input/SEditableTextBox.h"
#include "../../../../Slate/Public/Widgets/Layout/SBox.h"
#include "../../../../Slate/Public/Widgets/Layout/SSpacer.h"
#include "../../../../Slate/Public/Widgets/Input/SButton.h"
#include "../../../../UMG/Public/Components/VerticalBox.h"
#include "../../../../UMG/Public/Components/HorizontalBox.h"
#include "../../../../SlateCore/Public/Widgets/SWidget.h"
#include "../../../../SlateCore/Public/Widgets/SBoxPanel.h"
#include "../../../../Slate/Public/Framework/Application/SlateApplication.h"
#include "../../../../Slate/Public/Widgets/Docking/SDockTab.h"
#include "../../../../Core/Public/Internationalization/Text.h"

static const FName TPTabName("TP");

#define LOCTEXT_NAMESPACE "FTPModule"

void FTPModule::StartupModule()
{
	FTPStyle::Initialize();
	FTPStyle::ReloadTextures();

	FTPCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FTPCommands::Get().AddPullAndInsertTag,
		FExecuteAction::CreateRaw(this, &FTPModule::AddPullAndInsertFun),
		FCanExecuteAction());

	PluginCommands2 = MakeShareable(new FUICommandList);

	PluginCommands2->MapAction(
		FTPCommands::Get().AddScrewoutAndinTag,
		FExecuteAction::CreateRaw(this, &FTPModule::AddScrewoutAndinFun),
		FCanExecuteAction());

	PluginCommands3 = MakeShareable(new FUICommandList);

	PluginCommands3->MapAction(
		FTPCommands::Get().AddFadeAndDisplayTag,
		FExecuteAction::CreateRaw(this, &FTPModule::AddFadeAndDisplayFun),
		FCanExecuteAction());

	PluginCommands4 = MakeShareable(new FUICommandList);

	PluginCommands4->MapAction(
		FTPCommands::Get().AddShearPlate,
		FExecuteAction::CreateRaw(this, &FTPModule::AddShearPlateFun),
		FCanExecuteAction());

	PluginCommands5 = MakeShareable(new FUICommandList);

	PluginCommands5->MapAction(
		FTPCommands::Get().AddConstraintTag,
		FExecuteAction::CreateRaw(this, &FTPModule::AddConstraintTagFun),
		FCanExecuteAction());

	PluginCommands6 = MakeShareable(new FUICommandList);

	PluginCommands6->MapAction(
		FTPCommands::Get().AdditionConstraintTag,
		FExecuteAction::CreateRaw(this, &FTPModule::AdditionConstraintTagFun),
		FCanExecuteAction());

	PluginCommands7 = MakeShareable(new FUICommandList);

	PluginCommands7->MapAction(
		FTPCommands::Get().UnloadSpecificationTag,
		FExecuteAction::CreateRaw(this, &FTPModule::AddUnloadSpecificationFun),
		FCanExecuteAction());

	PluginCommands8 = MakeShareable(new FUICommandList);

	PluginCommands8->MapAction(
		FTPCommands::Get().LoadSpecificationTag,
		FExecuteAction::CreateRaw(this, &FTPModule::AddLoadSpecificationFun),
		FCanExecuteAction());

	PluginCommands9 = MakeShareable(new FUICommandList);

	PluginCommands9->MapAction(
		FTPCommands::Get().RepairSpecificationTag,
		FExecuteAction::CreateRaw(this, &FTPModule::AddRepairSpecificationFun),
		FCanExecuteAction());

	PluginCommands10 = MakeShareable(new FUICommandList);

	PluginCommands10->MapAction(
		FTPCommands::Get().NameAndTipTag,
		FExecuteAction::CreateRaw(this, &FTPModule::AddNameAndTipFun),
		FCanExecuteAction());

	PluginCommands11 = MakeShareable(new FUICommandList);

	PluginCommands11->MapAction(
		FTPCommands::Get().AddInputTag,
		FExecuteAction::CreateRaw(this, &FTPModule::AddInputTag),
		FCanExecuteAction());

	PluginCommands12 = MakeShareable(new FUICommandList);

	PluginCommands12->MapAction(
		FTPCommands::Get().but1,
		FExecuteAction::CreateRaw(this, &FTPModule::But1),
		FCanExecuteAction());

	PluginCommands13 = MakeShareable(new FUICommandList);

	PluginCommands13->MapAction(
		FTPCommands::Get().but2,
		FExecuteAction::CreateRaw(this, &FTPModule::But2),
		FCanExecuteAction());

	PluginCommands14 = MakeShareable(new FUICommandList);

	PluginCommands14->MapAction(
		FTPCommands::Get().but3,
		FExecuteAction::CreateRaw(this, &FTPModule::But3),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FTPModule::RegisterMenus));
}

TArray<FString> FTPModule::ReadCSVFile(const FString& FilePath)
{
	TArray<FString> CSVData;

	if (FPaths::FileExists(FilePath))
	{
		FFileHelper::LoadFileToStringArray(CSVData, *FilePath);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CSV file not found: %s"), *FilePath);
	}
	for (auto MyString : CSVData)
	{
		//Load Csv String
		//UE_LOG(LogTemp, Warning, TEXT("MyString: %s"), *MyString);
	}
	return CSVData;
}

void FTPModule::InputCSVToTags()
{
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (World)
	{
		int NotFindActors = 0;
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), Actors);

		FString ContentPath = FPaths::ProjectDir() + "//input.csv";
		TArray<FString> LoadTFS = ReadCSVFile(ContentPath);

		auto start_time = std::chrono::high_resolution_clock::now();

#pragma omp parallel for 
		for (FString InputString : LoadTFS)
		{
			TArray<FString> SplittedArray;
			InputString.ParseIntoArray(SplittedArray, TEXT(","), true);
			bool ThisTFSLoaded = false;
			for (AActor* Actor : Actors)
			{
				if (SplittedArray[1] == Actor->GetName())
				{
					TArray<FName> AddTags;
					for (int i = 2; i < SplittedArray.Num(); i++)
					{
						AddTags.Add(*SplittedArray[i]);
					}
					Actor->Tags = AddTags;
					ThisTFSLoaded = true;
				}

			}
			if (!ThisTFSLoaded)
			{
				NotFindActors++;
				/*
				FString Text = InputString;
				UE_LOG(LogTemp, Warning, TEXT("missing: %s"), *Text);
				*/
			}
		}

		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
		FString DurationCount = FString::Printf(TEXT("%lld"), duration.count());
		UE_LOG(LogTemp, Warning, TEXT("use time to: %s ms"), *DurationCount);
		UE_LOG(LogTemp, Warning, TEXT("not find actor num: %d"), NotFindActors);


		FText DialogText = FText::Format(
			LOCTEXT("PluginButtonDialogText", "Recover Done"),
			FText::FromString(TEXT("FTPModule::PluginButtonClicked()")),
			FText::FromString(TEXT("TP.cpp"))
		);
		FMessageDialog::Open(EAppMsgType::Ok, DialogText);
	}
}

void FTPModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FTPStyle::Shutdown();

	FTPCommands::Unregister();
}

void FTPModule::AddPullAndInsertFun()
{
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (World)
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), Actors);
		for (AActor* Actor : Actors)
		{
			if (Actor->IsSelected())
			{
				auto tags = Actor->Tags;
				FName p = "Action_Pullout";
				tags.Add(p);
				p = "Action_Insert";
				tags.Add(p);
				Actor->Tags = tags;
			}
		}
	}
}

void FTPModule::AddScrewoutAndinFun()
{
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (World)
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), Actors);
		for (AActor* Actor : Actors)
		{
			if (Actor->IsSelected())
			{
				auto tags = Actor->Tags;
				FName p = "Action_Screwout";
				tags.Add(p);
				p = "Action_Screwin";
				tags.Add(p);
				Actor->Tags = tags;
			}
		}
	}
}

void FTPModule::AddFadeAndDisplayFun()
{
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (World)
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), Actors);
		for (AActor* Actor : Actors)
		{
			if (Actor->IsSelected())
			{
				auto tags = Actor->Tags;
				FName p = "Action_Fade";
				tags.Add(p);
				p = "Action_Display";
				tags.Add(p);
				Actor->Tags = tags;
			}
		}
	}
}

void FTPModule::AddShearPlateFun()
{
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (World)
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), Actors);
		ConstraintTag = "Constraint+";
		bool IsFirst = true;
		for (AActor* Actor : Actors)
		{
			if (Actor->IsSelected())
			{
				auto tags = Actor->Tags;
				Actor->GetFName();
				FString Str;
				if (IsFirst)
				{
					Str = ConstraintTag.ToString() + Actor->GetFName().ToString();
					IsFirst = false;
				}
				else
				{
					Str = ConstraintTag.ToString() + ";" + Actor->GetFName().ToString();
				}
				FName Name(*Str);
				ConstraintTag = Name;
			}
		}
	}
}

void FTPModule::AddConstraintTagFun()
{
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (World)
	{
		FString Str = ConstraintTag.ToString();
		if (!Str.Contains(TEXT("Constraint+")))
		{
			FText DialogText = FText::Format(
				LOCTEXT("PluginButtonDialogText", "You Not Add Once Constraint Fun To Model"),
				FText::FromString(TEXT("FTPModule::PluginButtonClicked()")),
				FText::FromString(TEXT("TP.cpp"))
			); FMessageDialog::Open(EAppMsgType::Ok, DialogText);
		}
		else
		{
			TArray<AActor*> Actors;
			UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), Actors);
			for (AActor* Actor : Actors)
			{
				if (Actor->IsSelected())
				{
					int ChangeTagIndex = 0;
					auto tags = Actor->Tags;
					bool HadChange = false;
					for (FName tag : tags)
					{
						FString Strs(tag.ToString());
						if (Strs.Contains("Constraint+"))
						{
							HadChange = true;
							break;
						}
						ChangeTagIndex++;
					}
					if (HadChange)
					{
						tags[ChangeTagIndex] = ConstraintTag;
					}
					else
					{
						tags.Add(ConstraintTag);
					}
					Actor->Tags = tags;
				}
			}
			FText DialogText = FText::Format(
				LOCTEXT("PluginButtonDialogText", "Recover Done"),
				FText::FromString(TEXT("FTPModule::PluginButtonClicked()")),
				FText::FromString(TEXT("TP.cpp"))
			); FMessageDialog::Open(EAppMsgType::Ok, DialogText);
		}
	}
}

void FTPModule::AdditionConstraintTagFun()
{

	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (World)
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), Actors);
		for (AActor* Actor : Actors)
		{
			if (Actor->IsSelected())
			{
				int ChangeTagIndex = 0;
				bool HadChange = false;
				auto tags = Actor->Tags;
				FString AddSaved;
				for (FName tag : tags)
				{
					FString Str(tag.ToString());
					if (Str.Contains("Constraint+"))
					{
						FString SavedStr(ConstraintTag.ToString());
						TArray<FString> SavedArray;
						SavedStr.ParseIntoArray(SavedArray, TEXT("+"), true);
						AddSaved = SavedArray.Last();
						HadChange = true;
						break;
					}
					ChangeTagIndex++;
				}
				if (HadChange)
				{
					std::set<FString> SaveSet;
					TArray<FString> SavedArray;
					AddSaved.ParseIntoArray(SavedArray, TEXT(";"), true);
					for (FString arr : SavedArray)
					{
						SaveSet.insert(arr);
					}

					FString NewStr = tags[ChangeTagIndex].ToString();// +AddSaved;
					TArray<FString> SavedArray2;
					TArray<FString> SavedArray3;
					NewStr.ParseIntoArray(SavedArray2, TEXT("+"), true);
					SavedArray2.Last().ParseIntoArray(SavedArray3, TEXT(";"), true);
					for (FString arr : SavedArray3)
					{
						SaveSet.insert(arr);
					}

					FString OutputStr = "Constraint+";
					for (std::set<FString>::iterator it = SaveSet.begin(); it != SaveSet.end(); ++it) {
						if (it == SaveSet.begin())
						{
							OutputStr = OutputStr + *it;// +TEXT(";")
						}
						else
						{
							OutputStr = OutputStr + TEXT(";") + *it;
						}
					}

					FName Name(*OutputStr);
					tags[ChangeTagIndex] = Name;
				}
				else
				{
					tags.Add(ConstraintTag);
				}
				Actor->Tags = tags;
			}
		}

		FText DialogText = FText::Format(
			LOCTEXT("PluginButtonDialogText", "Addition Done"),
			FText::FromString(TEXT("FTPModule::PluginButtonClicked()")),
			FText::FromString(TEXT("TP.cpp"))
		); FMessageDialog::Open(EAppMsgType::Ok, DialogText);
	}
}

TSharedPtr<SWindow> InputWindow;
TArray<TSharedPtr<SEditableTextBox>> EditableTextBoxes;

void HandleTextCommitted(const FText& InText, ETextCommit::Type CommitType, int mode)
{
	if (CommitType == ETextCommit::OnEnter)
	{
		TArray<FString> EnteredTexts;

		for (const TSharedPtr<SEditableTextBox>& TextBox : EditableTextBoxes)
		{
			FString EnteredText = TextBox->GetText().ToString();
			EnteredTexts.Add(EnteredText);
		}

		FString CombinedText = FString::Join(EnteredTexts, TEXT("+"));
		CombinedText.RemoveFromStart(TEXT("+"));

		UWorld* World = GEditor->GetEditorWorldContext().World();
		if (World)
		{
			TArray<AActor*> Actors;
			UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), Actors);
			for (AActor* Actor : Actors)
			{
				if (Actor->IsSelected())
				{
					auto tags = Actor->Tags;
					bool hadTag = false;

					FString AddTag;
					int tagNum = 0;
					if (mode == 0)AddTag = "UnloadStep^";
					else if (mode == 1)AddTag = "LoadStep^";
					else if (mode == 2)AddTag = "ChangeStep^";

					for (auto tag : tags)
					{
						if (tag.ToString().Contains(AddTag))
						{
							hadTag = true;
							break;
						}
						tagNum++;
					}
					if (hadTag)
					{
						AddTag += CombinedText;
						FName p = *AddTag;
						tags[tagNum] = p;
						Actor->Tags = tags;
					}
					else
					{
						AddTag += CombinedText;
						FName p = *AddTag;
						tags.Add(p);
						Actor->Tags = tags;
					}
				}
			}
		}

		if (InputWindow.IsValid())
		{
			CombinedText.Empty();
			EditableTextBoxes.Empty();
			InputWindow->RequestDestroyWindow();
		}
	}
}

void CreateEditableTextBoxWithCloseButtonWidget(int mode)
{
	TSharedRef<SVerticalBox> VBox = SNew(SVerticalBox);

	for (int32 Index = 0; Index < 4; ++Index)
	{
		TSharedPtr<SEditableTextBox> TextBox = SNew(SEditableTextBox)
			.HintText(FText::Format(LOCTEXT("InputHint", "Enter text for Box {0} and press Enter"), Index + 1))
			.OnTextCommitted_Lambda([Index, mode](const FText& InText, ETextCommit::Type CommitType) {
			HandleTextCommitted(InText, CommitType, mode);
				});

		VBox->AddSlot()
			.AutoHeight()
			.HAlign(HAlign_Center)
			.Padding(10)
			[
				TextBox.ToSharedRef()
			];

		EditableTextBoxes.Add(TextBox);
	}

	InputWindow = SNew(SWindow)
		.Title(LOCTEXT("InputWindow", "Input Window"))
		.SizingRule(ESizingRule::UserSized)
		.ClientSize(FVector2D(300.0f, 200.0f))
		.IsPopupWindow(true)
		.Content()
		[
			VBox
		];

	FSlateApplication::Get().AddWindow(InputWindow.ToSharedRef());

	return;
}

void FTPModule::AddUnloadSpecificationFun()
{
	CreateEditableTextBoxWithCloseButtonWidget(0);
}

void FTPModule::AddLoadSpecificationFun()
{
	CreateEditableTextBoxWithCloseButtonWidget(1);
}

void FTPModule::AddRepairSpecificationFun()
{
	CreateEditableTextBoxWithCloseButtonWidget(2);
}

void FTPModule::AddNameAndTipFun()
{
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (World)
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), Actors);
		for (AActor* Actor : Actors)
		{
			if (Actor->IsSelected())
			{
				auto tags = Actor->Tags;
				FName p = "Name_";
				tags.Add(p);
				p = "Tip_";
				tags.Add(p);
				p = "Durab_";
				tags.Add(p);
				Actor->Tags = tags;
			}
		}
	}
}

TSharedRef<SWidget> CreateEditableTextBoxWithCloseButton(const FText& DefaultText, const FOnTextCommitted& OnTextCommittedCallback, FOnTextChanged OnTextChangedCallback, TSharedPtr<SWindow> InWindow)
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.Padding(5.f)
		[
			SNew(SEditableTextBox)
				.HintText(FText::FromString(TEXT("Enter text here,will add tag to selected actor")))
				.Text(DefaultText)
				.OnTextCommitted(OnTextCommittedCallback)
				.OnTextChanged(OnTextChangedCallback)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(5.f)
		[
			SNew(SButton)
				.Text(FText::FromString(TEXT("Close")))
				.OnClicked_Lambda([InWindow]() {
				InWindow->RequestDestroyWindow();
				return FReply::Handled();
					})
		];
}

void OnTextCommitted(const FText& InText, ETextCommit::Type CommitType)
{
	FString Text = InText.ToString();
	UE_LOG(LogTemp, Warning, TEXT("Entered text: %s"), *Text);

	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (World)
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), Actors);
		for (AActor* Actor : Actors)
		{
			if (Actor->IsSelected())
			{
				auto tags = Actor->Tags;
				bool hadThisTag = false;
				for (auto tag : tags)
				{
					if (FName(*Text) == tag)
						hadThisTag = true;
				}
				if (!hadThisTag)
				{
					FName p = FName(*Text);
					tags.Add(p);
					Actor->Tags = tags;
				}
			}
		}
	}
}

void OnTextChanged(const FText& InText)
{
	FString Text = InText.ToString();
	UE_LOG(LogTemp, Warning, TEXT("Modified text: %s"), *Text);
}

void FTPModule::AddInputTag()
{
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (World)
	{
		TSharedRef<SWindow> Window = SNew(SWindow)
			.Title(FText::FromString(TEXT("Editable Text Box with Close Button Widget")))
			.ClientSize(FVector2D(400.f, 120.f))
			.SupportsMaximize(false)
			.SupportsMinimize(false)
			.SizingRule(ESizingRule::FixedSize)
			.IsPopupWindow(true);

		TSharedRef<SWidget> MyTextBoxWithCloseButtonWidget = CreateEditableTextBoxWithCloseButton(
			FText::FromString(TEXT("")),
			FOnTextCommitted::CreateStatic(&OnTextCommitted),
			FOnTextChanged::CreateStatic(&OnTextChanged),
			Window
		);

		Window->SetContent(MyTextBoxWithCloseButtonWidget);
		FSlateApplication::Get().AddWindow(Window);
	}
}

void FTPModule::But1()
{
	TArray<FString> SaveText;
	FString SaveDirectory = FPaths::ProjectDir() + "\\Output";
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (World)
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), Actors);
		for (AActor* Actor : Actors)
		{
			if (Actor->IsSelected())
			{
				FString AddToSaveText = "";
				FString ActorName = Actor->GetActorLabel();
				FString NumberAsString = Actor->GetName();

				AddToSaveText += ActorName + ",";
				AddToSaveText += NumberAsString + ",";

				auto tags = Actor->Tags;
				for (FName tag : tags)
				{
					AddToSaveText += tag.ToString() + ",";
				}

				SaveText.Add(AddToSaveText);
			}
		}
		if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*SaveDirectory))
		{
			return;
		}
		FString FinalString = "";
		for (FString& Each : SaveText)
		{
			FinalString += Each;
			FinalString += LINE_TERMINATOR;
		}

		FDateTime CurrentTime = FDateTime::Now();

		SaveDirectory += FString::Printf(TEXT("%d - %d - %d %d - %d - %d"), CurrentTime.GetYear(), CurrentTime.GetMonth(), CurrentTime.GetDay(),
			CurrentTime.GetHour(), CurrentTime.GetMinute(), CurrentTime.GetSecond());

		SaveDirectory += ".csv";

		FFileHelper::SaveStringToFile(FinalString, *SaveDirectory, FFileHelper::EEncodingOptions::ForceUTF8);
	}
}

void FTPModule::But2()
{
	TArray<FString> SaveText;
	FString SaveDirectory = FPaths::ProjectDir() + "\\Output";
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (World)
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), Actors);
		auto start_time = std::chrono::high_resolution_clock::now();
#pragma omp parallel for 

		for (AActor* Actor : Actors)
		{
			FString AddToSaveText = "";

			FString ActorName = Actor->GetActorLabel();
			FString NumberAsString = Actor->GetName();


			AddToSaveText += ActorName + ",";
			AddToSaveText += NumberAsString + ",";

			auto tags = Actor->Tags;
			for (FName tag : tags)
			{
				AddToSaveText += tag.ToString() + ",";
			}

			SaveText.Add(AddToSaveText);
		}
		if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*SaveDirectory))
		{
			return;
		}
		FString FinalString = "";
		for (FString& Each : SaveText)
		{
			FinalString += Each;
			FinalString += LINE_TERMINATOR;
		}

		FDateTime CurrentTime = FDateTime::Now();

		SaveDirectory += FString::Printf(TEXT("%d - %d - %d %d - %d - %d"), CurrentTime.GetYear(), CurrentTime.GetMonth(), CurrentTime.GetDay(),
			CurrentTime.GetHour(), CurrentTime.GetMinute(), CurrentTime.GetSecond());

		SaveDirectory += ".csv";

		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
		FString DurationCount = FString::Printf(TEXT("%lld"), duration.count());
		UE_LOG(LogTemp, Warning, TEXT("use time to: %s ms"), *DurationCount);

		FFileHelper::SaveStringToFile(FinalString, *SaveDirectory, FFileHelper::EEncodingOptions::ForceUTF8);
	}
}

void FTPModule::But3()
{
	InputCSVToTags();
}

void FTPModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	/*
	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FTPCommands::Get().AddPullAndInsertTag, PluginCommands);
		}
	}
	*/

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FTPCommands::Get().AddPullAndInsertTag));
				Entry.SetCommandList(PluginCommands);
			}
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FTPCommands::Get().AddScrewoutAndinTag));
				Entry.SetCommandList(PluginCommands2);
			}
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FTPCommands::Get().AddFadeAndDisplayTag));
				Entry.SetCommandList(PluginCommands3);
			}

			FToolMenuSection& Section2 = ToolbarMenu->FindOrAddSection("PluginTools2");
			{
				FToolMenuEntry& Entry = Section2.AddEntry(FToolMenuEntry::InitToolBarButton(FTPCommands::Get().AddShearPlate));
				Entry.SetCommandList(PluginCommands4);
			}
			{
				FToolMenuEntry& Entry = Section2.AddEntry(FToolMenuEntry::InitToolBarButton(FTPCommands::Get().AddConstraintTag));
				Entry.SetCommandList(PluginCommands5);
			}
			{
				FToolMenuEntry& Entry = Section2.AddEntry(FToolMenuEntry::InitToolBarButton(FTPCommands::Get().AdditionConstraintTag));
				Entry.SetCommandList(PluginCommands6);
			}

			FToolMenuSection& Section3 = ToolbarMenu->FindOrAddSection("PluginTools3");
			{
				FToolMenuEntry& Entry = Section3.AddEntry(FToolMenuEntry::InitToolBarButton(FTPCommands::Get().UnloadSpecificationTag));
				Entry.SetCommandList(PluginCommands7);
			}
			{
				FToolMenuEntry& Entry = Section3.AddEntry(FToolMenuEntry::InitToolBarButton(FTPCommands::Get().LoadSpecificationTag));
				Entry.SetCommandList(PluginCommands8);
			}
			{
				FToolMenuEntry& Entry = Section3.AddEntry(FToolMenuEntry::InitToolBarButton(FTPCommands::Get().RepairSpecificationTag));
				Entry.SetCommandList(PluginCommands9);
			}

			FToolMenuSection& Section4 = ToolbarMenu->FindOrAddSection("PluginTools4");
			{
				FToolMenuEntry& Entry = Section4.AddEntry(FToolMenuEntry::InitToolBarButton(FTPCommands::Get().NameAndTipTag));
				Entry.SetCommandList(PluginCommands10);
			}
			{
				FToolMenuEntry& Entry = Section4.AddEntry(FToolMenuEntry::InitToolBarButton(FTPCommands::Get().AddInputTag));
				Entry.SetCommandList(PluginCommands11);
			}
			{
				FToolMenuEntry& Entry = Section4.AddEntry(FToolMenuEntry::InitToolBarButton(FTPCommands::Get().but1));
				Entry.SetCommandList(PluginCommands12);
			}
			{
				FToolMenuEntry& Entry = Section4.AddEntry(FToolMenuEntry::InitToolBarButton(FTPCommands::Get().but2));
				Entry.SetCommandList(PluginCommands13);
			}
			{
				FToolMenuEntry& Entry = Section4.AddEntry(FToolMenuEntry::InitToolBarButton(FTPCommands::Get().but3));
				Entry.SetCommandList(PluginCommands14);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FTPModule, TP)