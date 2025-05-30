////////////////////////////////////////////////////////////////
///		{MGC} : GENERATED CLASS * Do NOT edit!
////////////////////////////////////////////////////////////////

#pragma once

#include "Runtime/Core/Public/CoreMinimal.h"
#include "Runtime/CoreUObject/Public/UObject/Object.h"
#include "Runtime/CoreUObject/Public/UObject/ObjectMacros.h"
#include "Runtime/CoreUObject/Public/UObject/WeakObjectPtr.h"
#include "Runtime/CoreUObject/Public/UObject/SoftObjectPtr.h"
#include "Runtime/CoreUObject/Public/UObject/SoftObjectPath.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectIterator.h"

#include "../../Plugins\Marketplace\MagicNode\Source\MagicNodeRuntime\Public\MagicNodeRuntime.h"

#include "MagicNodeRuntime.h"
#include "MGC_TestCode__CPP.generated.h"








UCLASS()
class MNTASK_API UMGC_TestCode__CPP : public UMagicNode
{
	GENERATED_BODY()

public:

UFUNCTION (BlueprintCallable,Category="Magic Node",meta=(WorldContext="Context",BlueprintInternalUseOnly="true",ToolTip="UMGC_TestCode__CPP"))
 static void Execute(UObject* Context);

UFUNCTION (BlueprintCallable,Category="Magic Node",meta=(WorldContext="Context",BlueprintInternalUseOnly="true",ToolTip="UMGC_TestCode__CPP"))
 static FName GetFNamesss(FName nm);

bool IsTrue;


};

////////////////////////////////////////////////////////////////