////////////////////////////////////////////////////////////////
///		{MGC} : GENERATED SOURCE * Do NOT edit!
////////////////////////////////////////////////////////////////

#include "MGC_Task__CPP.h"

void UMGC_Task__CPP::Execute(
	UObject* Context,
	AActor* Actor,	
	const TArray<FString> &ArrayIN	)
{
	for(FName fn:Actor->Tags)
	{	
		FString fs=fn.ToString();
		//Ensure(Context);
		UE_LOG(LogTemp,Error,TEXT("Hello World! %s"),*fs);

	}
}

////////////////////////////////////////////////////////////////