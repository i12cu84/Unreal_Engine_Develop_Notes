// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FTPModule : public IModuleInterface
{
public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	void AddPullAndInsertFun();
	void AddScrewoutAndinFun();
	void AddFadeAndDisplayFun();

	void AddShearPlateFun();
	void AddConstraintTagFun();
	void AdditionConstraintTagFun();

	void AddUnloadSpecificationFun();
	void AddLoadSpecificationFun();
	void AddRepairSpecificationFun();

	void AddNameAndTipFun();
	void AddInputTag();
	void But1();
	void But2();
	void But3();

	FName ConstraintTag;
	bool HadConstraint = false;
	TArray<FString> ReadCSVFile(const FString& FilePath);
	void InputCSVToTags();
private:

	void RegisterMenus();
	
	TSharedPtr<class FUICommandList> PluginCommands;
	TSharedPtr<class FUICommandList> PluginCommands2;
	TSharedPtr<class FUICommandList> PluginCommands3;

	TSharedPtr<class FUICommandList> PluginCommands4;
	TSharedPtr<class FUICommandList> PluginCommands5;
	TSharedPtr<class FUICommandList> PluginCommands6;

	TSharedPtr<class FUICommandList> PluginCommands7;
	TSharedPtr<class FUICommandList> PluginCommands8;
	TSharedPtr<class FUICommandList> PluginCommands9;

	TSharedPtr<class FUICommandList> PluginCommands10;
	TSharedPtr<class FUICommandList> PluginCommands11;
	TSharedPtr<class FUICommandList> PluginCommands12;
	TSharedPtr<class FUICommandList> PluginCommands13;
	TSharedPtr<class FUICommandList> PluginCommands14;

};
