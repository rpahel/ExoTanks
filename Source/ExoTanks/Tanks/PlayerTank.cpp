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

	LaserSourcePoint = CreateDefaultSubobject<USceneComponent>("LaserSourcePoint");
	if (!LaserSourcePoint)
	{
		GLog->Log(ELogVerbosity::Error, "PlayerTank : Constructor -> LaserSourcePoint is null !");
		return;
	}
	LaserSourcePoint->SetupAttachment(CannonPivot);

	SplineMesh = CreateDefaultSubobject<USplineMeshComponent>("SplineMesh");
	if (!SplineMesh)
	{
		GLog->Log(ELogVerbosity::Error, "PlayerTank : Constructor -> SplineMesh is null !");
		return;
	}
	SplineMesh->SetupAttachment(LaserSourcePoint);
}

void APlayerTank::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsAiming)
		DrawLaser();
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

void APlayerTank::HideLaser()
{
	if (!SplineMesh || !LaserSourcePoint)
		return;

	SplineMesh->SetEndPosition(FVector::Zero());
}
#pragma endregion

#pragma region Overrides
void APlayerTank::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();
}
#pragma endregion

#pragma region Methods
void APlayerTank::DrawLaser()
{
	if (!World && !LaserSourcePoint)
		return;

	FVector splineMeshEnd = FVector::Zero();
	FVector rayStart = LaserSourcePoint->GetComponentLocation();
	FVector rayEnd = rayStart + AimRange * LaserSourcePoint->GetForwardVector().Normalize();
	TArray<FHitResult> outTankHits;
	FHitResult outObstacleHit;

	DrawDebugLine(
		World,
		rayStart,
		rayEnd,
		FColor::Emerald,
		false,
		1.f,
		0.1f
	);

	if (World->LineTraceSingleByChannel(outObstacleHit, rayStart, rayEnd, ECollisionChannel::ECC_Visibility))
	{
		GLog->Log(outObstacleHit.bBlockingHit ? "Blocking hit" : "Not Blocking Hit");
		GLog->Log("Hit " + outObstacleHit.GetActor()->GetName());

		TObjectPtr<ATank> tankHit = Cast<ATank>(outObstacleHit.GetActor());
		if (outObstacleHit.bBlockingHit && !tankHit)
		{
			rayEnd = outObstacleHit.ImpactPoint;
		}
	}

	if (World->LineTraceMultiByChannel(outTankHits, rayStart, rayEnd, ECollisionChannel::ECC_GameTraceChannel1))
	{
		for (FHitResult& hit : outTankHits)
		{
			TObjectPtr<ATank> tankHit = Cast<ATank>(hit.GetActor());

			if (tankHit)
			{
				GLog->Log(tankHit.GetName());
			}
		}
	}

	splineMeshEnd = FVector((rayEnd - rayStart).Length(), 0, 0);

	if (!SplineMesh)
		return;

	//SplineMesh->SetEndPosition(splineMeshEnd);
}
#pragma endregion