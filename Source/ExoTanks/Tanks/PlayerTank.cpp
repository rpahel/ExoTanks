// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTank.h"

#pragma region Public
APlayerTank::APlayerTank()
{
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	if (!CameraSpringArm)
	{
		GLog->Log(ELogVerbosity::Error, "PlayerTank : Constructor -> CameraSpringArm is null !");
		return;
	}
	CameraSpringArm->SetupAttachment(CannonPivot);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	if (!Camera)
	{
		GLog->Log(ELogVerbosity::Error, "PlayerTank : Constructor -> Camera is null !");
		return;
	}
	Camera->SetupAttachment(CameraSpringArm);
}
void APlayerTank::AddCannonRotation(const float& RotAmount) const
{
	if (!CannonPivot)
	{
		GLog->Log(ELogVerbosity::Error, "PlayerTank : AddCannonRotation() -> CannonPivot is null !");
		return;
	}

	FRotator relativeRot = CannonPivot->GetRelativeRotation();

	if ((RotAmount < 0 && relativeRot.Pitch > CannonRotationRange.X) ||
		(RotAmount > 0 && relativeRot.Pitch < CannonRotationRange.Y))
	{
		relativeRot.Add(RotAmount, 0, 0);
	}

	if (relativeRot.Pitch < CannonRotationRange.X)
		relativeRot.Pitch = CannonRotationRange.X;
	else if (relativeRot.Pitch > CannonRotationRange.Y)
		relativeRot.Pitch = CannonRotationRange.Y;

	CannonPivot->SetRelativeRotation(relativeRot);
}

void APlayerTank::AddTurretRotation(const float& RotAmount) const
{
	if (!TurretPivot)
	{
		GLog->Log(ELogVerbosity::Error, "PlayerTank : AddTurretRotation() -> TurretPivot is null !");
		return;
	}

	TurretPivot->AddRelativeRotation(FRotator(0, RotAmount, 0));
}

void APlayerTank::SetBodyRotationTarget(const FRotator& NewRotation) const
{
	FRotator smoothedRot = FMath::Lerp(BodyPivot->GetRelativeRotation(), NewRotation, BodyRotationLerpAlpha);
	BodyPivot->SetRelativeRotation(smoothedRot);
}
#pragma endregion