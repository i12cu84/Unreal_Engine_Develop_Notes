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

#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"

#include "MagicNodeRuntime.h"
#include "MGC_SimpleCharacterMovement__CPP.generated.h"









UCLASS()
class MNTASK_API UMGC_SimpleCharacterMovement__CPP : public UMagicNode
{
	GENERATED_BODY()

//////////////////////////////////////////////////
public:

UFUNCTION (BlueprintCallable,Category="Magic Node",meta=(WorldContext="Context",BlueprintInternalUseOnly="true",ToolTip="UMGC_SimpleCharacterMovement__CPP"))
 static void Execute (
	UObject* Context,
	ACharacter* Character,
	UMagicNode* &Out,
	float LookUpRate,
	float &TurnRate
);

//////////////////////////////////////////////////
protected:

	AWAKE()
	{
		CanTick = true;

		_InputComponent =
		Cast<UInputComponent>
		(
			_Character->FindComponentByClass
			(
				UInputComponent::StaticClass()
			)
		);

		Ensure(_InputComponent);

		_InputComponent->BindAction
		(
			"Jump",
			IE_Pressed,
			this, &UMGC_SimpleCharacterMovement__CPP::Jump
		);

		_InputComponent->BindAction
		(
			"Jump",
			IE_Released,
			this, &UMGC_SimpleCharacterMovement__CPP::JumpStop
		);

		_InputComponent->BindAxis
		(
			"MoveForward",
			this, &UMGC_SimpleCharacterMovement__CPP::MoveForward
		);

		_InputComponent->BindAxis
		(
			"MoveRight",
			this, &UMGC_SimpleCharacterMovement__CPP::MoveRight
		);

		_InputComponent->BindAxis
		(
			"TurnRate",
			this, &UMGC_SimpleCharacterMovement__CPP::TurnAtRate
		);

		_InputComponent->BindAxis
		(
			"LookUpRate",
			this, &UMGC_SimpleCharacterMovement__CPP::LookUpAtRate
		);

		_InputComponent->BindAxis
		(
			"Turn",
			this, &UMGC_SimpleCharacterMovement__CPP::ControllerYawInput
		);

		_InputComponent->BindAxis
		(
			"LookUp",
			this, &UMGC_SimpleCharacterMovement__CPP::ControllerPitchInput
		);
	};

//////////////////////////////////////////////////
protected:

	void Jump();
	void JumpStop();

	void MoveForward(float Value);
	void MoveRight(float Value);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	
	void ControllerYawInput(float Value);
	void ControllerPitchInput(float Value);

//////////////////////////////////////////////////
private:

	float _BaseTurnRate;
	float _BaseLookUpRate;

	ACharacter* _Character;
	UInputComponent* _InputComponent;

//////////////////////////////////////////////////

};

////////////////////////////////////////////////////////////////