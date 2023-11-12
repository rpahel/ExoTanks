// Fill out your copyright notice in the Description page of Project Settings.


#include "TankController.h"
#include "../../../../UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../../../../UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"

#pragma region Overrides
void ATankController::BeginPlay()
{
	Super::BeginPlay();

	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer());
	
	if (!InputSubsystem)
	{
		GLog->Log(ELogVerbosity::Error, "TankController : BeginPlay() -> Subsystem is nullptr !");
		return;
	}

	if (!InputMapping)
	{
		GLog->Log(ELogVerbosity::Error, "TankController : BeginPlay() -> InputMapping is nullptr !");
		return;
	}

	InputSubsystem->AddMappingContext(InputMapping, 0);

	PlayerTank = Cast<APlayerTank>(GetPawn());

	if (!PlayerTank)
	{
		GLog->Log(ELogVerbosity::Error, "TankController : BeginPlay() -> PlayerTank is nullptr !");
		return;
	}

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);

	if (!Input)
	{
		GLog->Log(ELogVerbosity::Error, "TankController : BeginPlay() -> Input is nullptr !");
		return;
	}

	Input->BindAction(TankLook, ETriggerEvent::Triggered, this, &ATankController::TankLookHandler);
	Input->BindAction(TankMovement, ETriggerEvent::Triggered, this, &ATankController::TankMovementHandler);
}

void ATankController::Destroyed()
{
	Super::Destroyed();

	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer());

	if (InputSubsystem && InputMapping)
		InputSubsystem->RemoveMappingContext(InputMapping);
}
#pragma endregion



#pragma region Event Handlers
void ATankController::TankLookHandler(const FInputActionValue& Value)
{
	FVector2D Axis2DValue = MouseSensitivity * Value.Get<FVector2D>();

	if (PlayerTank)
	{
		PlayerTank->AddCannonRotation(Axis2DValue.Y);
		PlayerTank->AddTurretRotation(Axis2DValue.X);
	}
}

void ATankController::TankMovementHandler(const FInputActionValue& Value)
{
	FVector2D axis2DValue = Value.Get<FVector2D>().GetSafeNormal();
	FVector vector3D = FVector(axis2DValue.X, axis2DValue.Y, 0);

	if (PlayerTank)
	{
		PlayerTank->AddMovementInput(
			vector3D,
			1.f);

		PlayerTank->SetBodyRotation(vector3D.ToOrientationRotator());
	}
}
#pragma endregion