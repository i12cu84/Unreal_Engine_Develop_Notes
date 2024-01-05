// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPStyle.h"
#include "TP.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FTPStyle::StyleInstance = nullptr;

void FTPStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FTPStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FTPStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("TPStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FTPStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("TPStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("TP")->GetBaseDir() / TEXT("Resources"));

	Style->Set("TP.AddPullAndInsertTag", new IMAGE_BRUSH_SVG(TEXT("home"), Icon20x20));
	Style->Set("TP.AddScrewoutAndinTag", new IMAGE_BRUSH_SVG(TEXT("360-degrees"), Icon20x20));
	Style->Set("TP.AddFadeAndDisplayTag", new IMAGE_BRUSH_SVG(TEXT("add-document"), Icon20x20));

	Style->Set("TP.AddShearPlate", new IMAGE_BRUSH_SVG(TEXT("add-folder"), Icon20x20));
	Style->Set("TP.AddConstraintTag", new IMAGE_BRUSH_SVG(TEXT("address-book"), Icon20x20));
	Style->Set("TP.AdditionConstraintTag", new IMAGE_BRUSH_SVG(TEXT("album-circle-plus"), Icon20x20));

	Style->Set("TP.UnloadSpecificationTag", new IMAGE_BRUSH_SVG(TEXT("apps-add"), Icon20x20));
	Style->Set("TP.LoadSpecificationTag", new IMAGE_BRUSH_SVG(TEXT("apps-delete"), Icon20x20));
	Style->Set("TP.RepairSpecificationTag", new IMAGE_BRUSH_SVG(TEXT("browsers"), Icon20x20));

	Style->Set("TP.NameAndTipTag", new IMAGE_BRUSH_SVG(TEXT("home"), Icon20x20));
	Style->Set("TP.AddInputTag", new IMAGE_BRUSH_SVG(TEXT("360-degrees"), Icon20x20));

	Style->Set("TP.But1", new IMAGE_BRUSH_SVG(TEXT("add-folder"), Icon20x20));
	Style->Set("TP.But2", new IMAGE_BRUSH_SVG(TEXT("address-book"), Icon20x20));
	Style->Set("TP.But3", new IMAGE_BRUSH_SVG(TEXT("album-circle-plus"), Icon20x20));


	return Style;
}

void FTPStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FTPStyle::Get()
{
	return *StyleInstance;
}
