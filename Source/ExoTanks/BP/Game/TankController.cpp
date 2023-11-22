// Fill out your copyright notice in the Description page of Project Settings.


#include "TankController.h"
#include "ExoTanks/BP/Actors/Tanks/PlayerTank.h"
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
	Input->BindAction(TankMovement, ETriggerEvent::Completed, this, &ATankController::TankMovementStopped);
	Input->BindAction(TankMovement, ETriggerEvent::Canceled, this, &ATankController::TankMovementStopped);
	Input->BindAction(Aim, ETriggerEvent::Started, this, &ATankController::TankAimStart);
	Input->BindAction(Aim, ETriggerEvent::Completed, this, &ATankController::TankAimComplete);
	Input->BindAction(Shoot, ETriggerEvent::Started, this, &ATankController::TankShoot);
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
	FRotator orientationRot = vector3D.ToOrientationRotator();

	if (PlayerTank)
	{
		FRotator targetRot = PlayerTank->GetTurretRotator() + orientationRot;

		PlayerTank->MoveTowards(
			targetRot.Vector(),
			1.f);
		
		PlayerTank->SetBodyRotationTarget(targetRot);
	}
}

void ATankController::TankMovementStopped(const FInputActionValue& Value)
{
	if (!PlayerTank)
		return;

	PlayerTank->SetIsMoving(false);
}

void ATankController::TankAimStart(const FInputActionValue& Value)
{
	if (!PlayerTank)
		return;

	PlayerTank->SetIsAiming(true);
}

void ATankController::TankAimComplete(const FInputActionValue& Value)
{
	if (!PlayerTank)
		return;

	PlayerTank->SetIsAiming(false);
	PlayerTank->HideLaser();
}

void ATankController::TankShoot(const FInputActionValue& Value)
{
	PlayerTank->Shoot();
}
#pragma endregion