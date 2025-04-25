// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "TPStyle.h"

class FTPCommands : public TCommands<FTPCommands>
{
public:

	FTPCommands()
		: TCommands<FTPCommands>(TEXT("TP"), NSLOCTEXT("Contexts", "TP", "TP Plugin"), NAME_None, FTPStyle::GetStyleSetName())
	{
	}

	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > AddPullAndInsertTag;
	TSharedPtr< FUICommandInfo > AddScrewoutAndinTag; 
	TSharedPtr< FUICommandInfo > AddFadeAndDisplayTag;

	TSharedPtr< FUICommandInfo > AddShearPlate;
	TSharedPtr< FUICommandInfo > AddConstraintTag;
	TSharedPtr< FUICommandInfo > AdditionConstraintTag;

	TSharedPtr< FUICommandInfo > UnloadSpecificationTag;
	TSharedPtr< FUICommandInfo > LoadSpecificationTag;
	TSharedPtr< FUICommandInfo > RepairSpecificationTag;

	TSharedPtr< FUICommandInfo > NameAndTipTag;
	TSharedPtr< FUICommandInfo > AddInputTag;
	TSharedPtr< FUICommandInfo > but1;
	TSharedPtr< FUICommandInfo > but2;
	TSharedPtr< FUICommandInfo > but3;

};
