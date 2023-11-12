// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerTank.generated.h"

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

	//==== Components ====

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraSpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

public:
	APlayerTank();

	void AddCannonRotation(const float& RotAmount) const;
	void AddTurretRotation(const float& RotAmount) const;
	void SetBodyRotationTarget(const FRotator& NewRotation) const;
};
