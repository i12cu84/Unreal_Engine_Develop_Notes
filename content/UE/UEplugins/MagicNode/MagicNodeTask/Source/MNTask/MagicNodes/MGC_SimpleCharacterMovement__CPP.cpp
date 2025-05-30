////////////////////////////////////////////////////////////////
///		{MGC} : GENERATED SOURCE * Do NOT edit!
////////////////////////////////////////////////////////////////

#include "MGC_SimpleCharacterMovement__CPP.h"

/////////////////////////////////////////////////////////////////
void UMGC_SimpleCharacterMovement__CPP::Execute (
	UObject* Context,
	ACharacter* Character,
	UMagicNode* &Out,
	float LookUpRate,
	float &TurnRate
) {
	Ensure(Context);
	Ensure(Character);

	auto Runtime = Enroll(Context,UMGC_SimpleCharacterMovement__CPP);

	Runtime->_Character = Character;
	Runtime->_BaseTurnRate = TurnRate;
	Runtime->_BaseLookUpRate = LookUpRate;

	Runtime->Run();

	/// If we want the Node to keep running,
	/// we have to hold a reference to it,
	/// to prevent GC from killing Node's Runtime:
	Out = Runtime;
}

/////////////////////////////////////////////////////////////////

void UMGC_SimpleCharacterMovement__CPP::Jump()
{
	if (_Character->CanJump())
	{
		_Character->Jump();
	}
}

void UMGC_SimpleCharacterMovement__CPP::JumpStop()
{
	_Character->StopJumping();
}

void UMGC_SimpleCharacterMovement__CPP::MoveForward(float Value)
{
	if ((_Character->Controller != NULL)&&(Value != 0.0f))
	{
		const FRotator Rotation =
			_Character->Controller->GetControlRotation();

		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction =
			FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		_Character->AddMovementInput(Direction, Value);
	}
}

void UMGC_SimpleCharacterMovement__CPP::MoveRight(float Value)
{
	if ((_Character->Controller != NULL)&&(Value != 0.0f))
	{
		const FRotator Rotation =
			_Character->Controller->GetControlRotation();

		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction =
			FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		_Character->AddMovementInput(Direction, Value);
	}
}

void UMGC_SimpleCharacterMovement__CPP::TurnAtRate(float Rate)
{
	_Character->AddControllerYawInput
	(
		Rate * _BaseTurnRate * TickDelta
	);
}

void UMGC_SimpleCharacterMovement__CPP::LookUpAtRate(float Rate)
{
	_Character->AddControllerPitchInput	
	(
		Rate * _BaseLookUpRate * TickDelta
	);
}

void UMGC_SimpleCharacterMovement__CPP::ControllerYawInput(float Value)
{
	_Character->AddControllerYawInput(Value);
}

void UMGC_SimpleCharacterMovement__CPP::ControllerPitchInput(float Value)
{
	_Character->AddControllerPitchInput(Value);
}

/////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////