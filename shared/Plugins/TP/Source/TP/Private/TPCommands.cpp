// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPCommands.h"

#define LOCTEXT_NAMESPACE "FTPModule"

void FTPCommands::RegisterCommands()
{
	UI_COMMAND(AddPullAndInsertTag, "None","添加拔出、插入动作", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(AddScrewoutAndinTag, "None","添加旋入、旋出动作", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(AddFadeAndDisplayTag, "None","添加渐隐、渐显动作", EUserInterfaceActionType::Button, FInputChord());

	UI_COMMAND(AddShearPlate, "None","录入约束关系", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(AddConstraintTag, "None","覆盖约束关系", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(AdditionConstraintTag, "None","附加约束关系", EUserInterfaceActionType::Button, FInputChord());

	UI_COMMAND(UnloadSpecificationTag, "None","添加拆卸时显示窗口说明内容", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(LoadSpecificationTag, "None","添加安装时显示窗口说明内容", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(RepairSpecificationTag, "None","添加调整时显示窗口说明内容", EUserInterfaceActionType::Button, FInputChord());
	
	UI_COMMAND(NameAndTipTag, "None","显示命名、提示、耐久度", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(AddInputTag, "None","添加输入窗口", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(but1, "None", "导出选中模型的信息", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(but2, "None", "导出所有模型的信息", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(but3, "None", "导入所有模型到工程", EUserInterfaceActionType::Button, FInputChord());

}

#undef LOCTEXT_NAMESPACE
