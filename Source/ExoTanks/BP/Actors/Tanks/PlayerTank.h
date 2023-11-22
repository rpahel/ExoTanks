// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "PlayerTank.generated.h"

class USpringArmComponent;
class USplineMeshComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS(Blueprintable)
class EXOTANKS_API APlayerTank : public ATank
{
	GENERATED_BODY()

private:
	//==== Exposed Fields ====

	UPROPERTY(EditAnywhere)
	float BodyRotationLerpAlpha = 0.05f;

	UPROPERTY(EditAnywhere)
	float AimRange = 1000.f;

	//==== Fields ====
	
	bool IsAiming = false;
	
	UPROPERTY()
	UWorld* World;

	//==== Components ====

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraSpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* LaserSourcePoint;

	UPROPERTY(VisibleAnywhere)
	USplineMeshComponent* SplineMesh;

public:
	APlayerTank();

	virtual void Tick(float DeltaSeconds) override;

	void AddCannonRotation(const float& RotAmount) const;
	void AddTurretRotation(const float& RotAmount) const;
	void SetBodyRotationTarget(const FRotator& NewRotation) const;
	void SetIsAiming(bool bIsAiming) { this->IsAiming = bIsAiming; }
	void HideLaser();

private:
	//==== Overrides ====

	virtual void BeginPlay();

	//==== Methods ====

	void DrawLaser();
};
